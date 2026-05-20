#!/usr/bin/env python3
# masters_ihm2.py — IHM MASTERS (plein écran adaptatif)
# Codé le 18/05

import tkinter as tk
from tkinter import ttk
import subprocess
import threading
import time
import os
import signal

# ─────────────────────────────────────────────
#  Couleurs
# ─────────────────────────────────────────────
BG          = "#eef2f7"   # fond bleu-gris très clair
BG2         = "#ffffff"   # colonnes blanc
BG3         = "#2e4057"   # header/footer bleu ardoise foncé
ACCENT      = "#ffffff"   # titre des colonnes
GREEN       = "#06d6a0"   # vert menthe pour statuts positifs
YELLOW      = "#ffd166"   # jaune doux pour avertissements
WHITE       = "#ffffff"   # blanc pour texte sur fonds foncés
GREY        = "#546e7a"   # gris bleuté plus foncé, lisible mais neutre
BTN_RED     = "#ef476f"   # rose-rouge pour danger
BTN_GREEN   = "#06d6a0"   # vert menthe pour démarrer
BTN_BLUE    = "#118ab2"   # bleu pour PLAY
BTN_ORANGE  = "#fd9e02"   # orange pour confirmer
BTN_GREY    = "#6b7280"   # gris pour boutons neutres

SCENARIO_COLORS = {
    "Push":  "#118ab2",
    "Punch": "#ef476f",
    "Touch": "#06d6a0",
}

# Ajouté le 20/04 à 16h30 — valeurs hardcodées pour le mode Touch
TOUCH_LOCKED = {
    'Force cible (N)':   1.0,
    'Force wrench (N)':  10.0,
    'Offset pré-P1 (m)': 0.05,
}

CMDS = [
    "ros2 launch ur_robot_driver ur_control.launch.py ur_type:=ur3e robot_ip:=192.168.1.101 use_fake_hardware:=false launch_rviz:=false",
    "ros2 run ros_tcp_endpoint default_server_endpoint --ros-args -p ROS_IP:=0.0.0.0",
    "bash -c 'cd ~/ira2_ws && ros2 run ur_safety_monitor safety_monitor_node'",
    "bash -c 'cd ~/ira2_ws && ros2 run ur_motion_manager motion_manager_node2'",
]
CMD_LABELS = ["UR Driver", "TCP Endpoint", "Safety Monitor", "Motion Manager"]

TOPIC_COMMAND = "/masters/command"
TOPIC_ABORT   = "/safety_abort"


class MastersIHM(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("MASTERS — Interface de contrôle")
        self.configure(bg=BG)

        # ── Fenêtré ──
        # self.geometry("1600x900")
        # self.state('zoomed')
        self.geometry(f"{self.winfo_screenwidth()}x{self.winfo_screenheight()}+0+0")
        self.resizable(True, True)
        self.update_idletasks()
        self.W = 1920
        self.H = 1080

        # ── Échelles relatives (référence 1920×1080) ──
        self.sx = self.W / 1920
        self.sy = self.H / 1080

        # ── État ──
        self.scenario_var  = tk.StringVar(value="Push")
        self.force_target  = tk.DoubleVar(value=10.0)
        self.force_wrench  = tk.DoubleVar(value=50.0)
        self.force_max     = tk.DoubleVar(value=200.0)
        self.offset_var    = tk.DoubleVar(value=0.001)
        self.timeout_var   = tk.DoubleVar(value=30.0)
        self.hold_time_var = tk.DoubleVar(value=0.0)

        self.processes      = {}
        self.ros_running    = False
        self.session_active = False

        # Ajouté le 20/04 — valeurs de référence pour envoi différentiel
        self._confirmed_params = {
            'force_target': 10.0,
            'force_wrench': 50.0,
            'force_max':    200.0,
            'offset':        0.001,
            'timeout':      30.0,
            'hold_time':     0.0,
        }

        # ── Status listener ──
        self._status_thread = None
        self._status_stop   = threading.Event()

        # Ajouté le 20/04 à 12h25 — dictionnaire des zones de log par nœud
        self._log_boxes = {}

        # Ajouté le 20/04 à 16h30 — références aux widgets sliders/entries pour blocage Touch
        self._slider_widgets = {}

        self._pre_touch_values = {}  # Ajouté le 21/04

        # ── Build ──
        self._build_header()
        self._build_body()
        self._build_status_bar()
        # self._build_footer()

        # Ajouté le 22/04 — griser les boutons au démarrage
        self._btn_cal.config(state="disabled")
        for btn in self._scen_btns.values():
            btn.config(state="disabled")
        self._btn_confirm.config(state="disabled")
        self._btn_stop.config(state="disabled") # Ajouté le 22/04 à 15h00
        self._btn_reset.config(state="disabled") # Ajouté le 22/04 à 15h55
        # Ajouté le 18/05
        self._btn_reset_anim.config(state="disabled")

        for lbl, (scale, entry, entry_var, var) in self._slider_widgets.items():
            scale.config(state="disabled")
            entry.config(state="disabled")

        self.protocol("WM_DELETE_WINDOW", self._on_close)

    def s(self, n):  return int(n * self.sx)
    def sv(self, n): return int(n * self.sy)
    def sf(self, n): return max(8, int(n * min(self.sx, self.sy)))

    # ══════════════════════════════════════════
    #  HEADER
    # ══════════════════════════════════════════
    def _build_header(self):
        frm = tk.Frame(self, bg=BG3, height=self.sv(80))
        frm.pack(fill="x")
        frm.pack_propagate(False)

        tk.Label(frm, text="⚙  MASTERS",
                 font=("Helvetica", self.sf(28), "bold"),
                 bg=BG3, fg=WHITE).pack(side="left", padx=self.s(30), pady=self.sv(15))

        ind_frm = tk.Frame(frm, bg=BG3)
        ind_frm.pack(side="right", padx=self.s(30))
        self._indicators = {}
        for key, label in [("ros","ROS2"),("robot","Robot"),("unity","Unity"),("session","Session")]:
            sub = tk.Frame(ind_frm, bg=BG3)
            sub.pack(side="left", padx=self.s(14))
            dot = tk.Label(sub, text="●", font=("Helvetica", self.sf(20)), bg=BG3, fg=GREY)
            dot.pack(side="left")
            tk.Label(sub, text=label, font=("Helvetica", self.sf(11)),
                     bg=BG3, fg=WHITE).pack(side="left", padx=4)
            self._indicators[key] = dot

    # ══════════════════════════════════════════
    #  BODY — 3 colonnes
    # ══════════════════════════════════════════
    def _build_body(self):
        body = tk.Frame(self, bg=BG)
        body.pack(fill="both", expand=True, padx=self.s(20), pady=self.sv(20))
        body.columnconfigure(0, weight=1)
        body.columnconfigure(1, weight=2)
        body.columnconfigure(2, weight=1)
        body.rowconfigure(0, weight=1)

        self._build_col_calibration(body)
        self._build_col_parametrage(body)
        self._build_col_controle(body)

    # ── Colonne 1 : Calibration ──
    def _build_col_calibration(self, parent):
        col = tk.Frame(parent, bg=BG2)
        col.grid(row=0, column=0, sticky="nsew", padx=self.s(8), pady=self.sv(8))

        self._col_title(col, "Calibration")

        tk.Label(col,
            text ="Calibration :\nOuvre la scène de calibration Unity.\nÀ faire si le robot a été déplacé depuis la dernière session.",
            font=("Helvetica", self.sf(11)), bg=BG2, fg=GREY,
            justify="left").pack(anchor="w", padx=self.s(20), pady=self.sv(14))

        self._btn_cal = self._card_button(col, "Calibration",
                                             BTN_GREY, self.sf(14), self._do_calibration)

        self._cal_status = tk.Label(col, text="",
                                    font=("Helvetica", self.sf(10)),
                                    bg=BG2, fg=YELLOW,
                                    wraplength=self.s(300), justify="left")
        self._cal_status.pack(anchor="w", padx=self.s(20), pady=self.sv(16))

    # ── Colonne 2 : Paramétrage ──
    def _build_col_parametrage(self, parent):
        col = tk.Frame(parent, bg=BG2)
        col.grid(row=0, column=1, sticky="nsew", padx=self.s(8), pady=self.sv(8))

        self._col_title(col, "Paramétrage")

        tk.Label(col, text="Choisir le scénario :",
                 font=("Helvetica", self.sf(12), "bold"),
                 bg=BG2, fg="#2e4057").pack(anchor="w", padx=self.s(20), pady=(self.sv(10), self.sv(4)))

        scen_row = tk.Frame(col, bg=BG2)
        scen_row.pack(fill="x", padx=self.s(20), pady=(0, self.sv(16)))

        self._scen_btns = {}
        for name, color in SCENARIO_COLORS.items():
            btn = tk.Button(scen_row, text=name,
                            font=("Helvetica", self.sf(13), "bold"),
                            bg=GREY, fg=WHITE, relief="flat",
                            activebackground=color, cursor="hand2",
                            command=lambda n=name: self._select_scenario(n))
            btn.pack(side="left", padx=self.s(6), ipady=self.sv(10), ipadx=self.s(18))
            self._scen_btns[name] = btn
        for n, btn in self._scen_btns.items():
            btn.config(bg=GREY)

        tk.Frame(col, bg=GREY, height=1).pack(fill="x", padx=self.s(20), pady=self.sv(4))

        params_row = tk.Frame(col, bg=BG2)
        params_row.pack(fill="x", padx=self.s(20), pady=(self.sv(10), self.sv(4)))
        tk.Label(params_row, text="Paramètres :",
                font=("Helvetica", self.sf(12), "bold"),
                bg=BG2, fg="#2e4057").pack(side="left")
        self._btn_reset = tk.Button(params_row, text="Réinitialiser",
                font=("Helvetica", self.sf(9)),
                bg=BTN_GREY, fg=WHITE, relief="flat",
                cursor="hand2",
                command=self._do_reset_params)
        self._btn_reset.pack(side="right")

        sliders_frm = tk.Frame(col, bg=BG2)
        sliders_frm.pack(fill="x", padx=self.s(20), pady=(self.sv(8), 0))
        sliders_frm.columnconfigure(0, weight=1)
        sliders_frm.columnconfigure(1, weight=1)

        params = [
            ("Force cible (N)",   self.force_target,  1.0, 79.0, 1.0),
            ("Force de poussée (N)",  self.force_wrench,  1.0, 150.0, 1.0),
            ("Force limite (N)",     self.force_max,     1.0, 200.0, 1.0),
            ("Distance avant contact (m)", self.offset_var,   0.001,  0.3, 0.001),
            ("Timeout (s)",       self.timeout_var,   5.0,  60.0, 1.0),
            ("Maintien (s)",      self.hold_time_var, 0.0,   5.0, 0.1),
        ]
        for i, (label, var, mn, mx, res) in enumerate(params):
            self._slider_row(sliders_frm, label, var, mn, mx, i // 2, i % 2)

        tk.Frame(col, bg=GREY, height=1).pack(fill="x", padx=self.s(20), pady=self.sv(14))

        self._btn_confirm = self._card_button(col, "✔  Confirmer les paramètres",
                                              BTN_ORANGE, self.sf(13), self._do_confirm)
        self._confirm_status = tk.Label(col, text="",
                                        font=("Helvetica", self.sf(10)),
                                        bg=BG2, fg="#2e4057", wraplength=self.s(500))
        self._confirm_status.pack(pady=self.sv(6))

    # ── Colonne 3 : Contrôle ──
    def _build_col_controle(self, parent):
        col = tk.Frame(parent, bg=BG2)
        col.grid(row=0, column=2, sticky="nsew", padx=self.s(8), pady=self.sv(8))

        self._col_title(col, "Contrôle")

        for i, txt in enumerate([
            "① Lancer les nœuds ROS2.",
            "② Mettre le casque VR.",
            "③ Lancer la simulation.",
        ]):
            tk.Label(col, text=txt, font=("Helvetica", self.sf(11)),
                     bg=BG2, fg=GREY).pack(anchor="w", padx=self.s(20),
                                           pady=(self.sv(10) if i == 0 else 0, 0))

        tk.Frame(col, bg=GREY, height=1).pack(fill="x", padx=self.s(20), pady=self.sv(8))

        self._btn_start = self._card_button(col, "▶  DÉMARRER",
                                            BTN_GREEN, self.sf(16), self._do_start)

        tk.Frame(col, bg=GREY, height=1).pack(fill="x", padx=self.s(20), pady=self.sv(8))

        # Ajouté le 18/05
        play_row = tk.Frame(col, bg=BG2)
        play_row.pack(fill="x", padx=self.s(20), pady=self.sv(4))

        # Ajouté le 18/05
        self._btn_play = tk.Button(play_row, text="🎮  PLAY",
                                   font=("Helvetica", self.sf(16), "bold"),
                                   bg=GREY, fg=WHITE, relief="flat",
                                   activebackground=BTN_BLUE, cursor="hand2",
                                   command=self._do_play, state="disabled")
        self._btn_play.pack(side="left", fill="x", expand=True, ipady=self.sv(14), padx=(0, self.s(4)))

        # Ajouté le 18/05
        self._btn_reset_anim = tk.Button(play_row, text="↺",
                                         font=("Helvetica", self.sf(16), "bold"),
                                         bg=GREY, fg=WHITE, relief="flat",
                                         activebackground=BTN_BLUE, cursor="hand2",
                                         command=self._do_reset_animation, state="disabled")
        self._btn_reset_anim.pack(side="left", ipady=self.sv(14), ipadx=self.s(16))

        tk.Frame(col, bg=GREY, height=1).pack(fill="x", padx=self.s(20), pady=self.sv(8))

        self._btn_stop = self._card_button(col, "⛔  STOP",
                                           BTN_RED, self.sf(16), self._do_stop)

        # Zone de logs avec onglets
        tk.Frame(col, bg=GREY, height=1).pack(fill="x", padx=self.s(20), pady=self.sv(4))

        log_header = tk.Frame(col, bg=BG2)
        log_header.pack(fill="x", padx=self.s(20))
        tk.Label(log_header, text="Logs :",
                 font=("Helvetica", self.sf(9), "bold"),
                 bg=BG2, fg=GREY).pack(side="left")
        tk.Button(log_header, text="🗑 Effacer",
                  font=("Helvetica", self.sf(8)),
                  bg=BTN_GREY, fg=WHITE, relief="flat",
                  activebackground=BTN_GREY, cursor="hand2",
                  command=self._clear_logs).pack(side="right")

        style = ttk.Style()
        style.theme_use('default')
        style.configure("TNotebook", background=BG2, borderwidth=0)
        style.configure("TNotebook.Tab", background=BG3, foreground=WHITE,
                        font=("Helvetica", self.sf(8)), padding=[self.s(6), self.sv(3)])
        style.map("TNotebook.Tab",
                  background=[("selected", BG)],
                  foreground=[("selected", "#2e4057")])

        self._notebook = ttk.Notebook(col)
        self._notebook.pack(fill="both", expand=True, padx=self.s(20), pady=self.sv(4))

        for label in CMD_LABELS:
            frame = tk.Frame(self._notebook, bg=BG)
            self._notebook.add(frame, text=label)
            box = tk.Text(frame,
                          font=("Courier", self.sf(8)),
                          bg="black",
                          fg="#00ff00",
                          relief="flat",
                          state="disabled",
                          wrap="word")
            box.pack(fill="both", expand=True)
            self._log_boxes[label] = box

    # ══════════════════════════════════════════
    #  STATUS BAR
    # ══════════════════════════════════════════
    def _build_status_bar(self):
        self._status_bar = tk.Frame(self, bg=GREY, height=self.sv(60))
        self._status_bar.pack(fill="x")
        self._status_bar.pack_propagate(False)
        self._status_label = tk.Label(
            self._status_bar,
            text="▶  Appuyez sur DÉMARRER pour lancer les nœuds ROS2.",
            font=("Helvetica", self.sf(14), "bold"),
            bg=GREY, fg=WHITE
        )
        self._status_label.pack(expand=True)

    def _set_status(self, text, color):
        self._status_bar.config(bg=color)
        self._status_label.config(text=text, bg=color)

    # ══════════════════════════════════════════
    #  ACTIONS
    # ══════════════════════════════════════════
    def _do_calibration(self):
        self._cal_status.config(text="⏳ Calibration en cours...", fg=YELLOW)
        cmd = 'ros2 service call /set_scenario masters_msgs/srv/SystemStateService "{command: 0}"'
        def run():
            try:
                subprocess.run(cmd, shell=True, capture_output=True, timeout=5)
            except subprocess.TimeoutExpired:
                pass
        threading.Thread(target=run, daemon=True).start()
        self.after(1500, lambda: self._cal_status.config(
            text="", fg=GREEN))

    def _select_scenario(self, name):
        self.scenario_var.set(name)
        for n, btn in self._scen_btns.items():
            btn.config(bg=SCENARIO_COLORS[n] if n == name else GREY)
        scen_map = {"Push": 3, "Punch": 2, "Touch": 4}
        scen = scen_map[name]
        cmd = f'ros2 service call /set_scenario masters_msgs/srv/SystemStateService "{{command: {scen}}}"'
        def run():
            try:
                subprocess.run(cmd, shell=True, capture_output=True, timeout=5)
            except subprocess.TimeoutExpired:
                pass
        threading.Thread(target=run, daemon=True).start()

        # Ajouté le 18/05
        self._do_reset_animation()

        if name == "Touch":
            print(f"[DEBUG] Passage en Touch — _pre_touch_values AVANT sauvegarde : {self._pre_touch_values}")
            print(f"[DEBUG] Valeurs actuelles — force_target:{self.force_target.get()}, force_wrench:{self.force_wrench.get()}, offset:{self.offset_var.get()}")

            if self.force_target.get() != 1.0 or self.force_wrench.get() != 10.0 or self.offset_var.get() != 0.05:
                self._pre_touch_values = {
                    'Force cible (N)':    self.force_target.get(),
                    'Force wrench (N)':   self.force_wrench.get(),
                    'Offset pré-P1 (m)':  self.offset_var.get(),
                }
            for lbl, locked_val in TOUCH_LOCKED.items():
                if lbl in self._slider_widgets:
                    scale, entry, entry_var, var = self._slider_widgets[lbl]
                    var.set(locked_val)
                    entry_var.set(f"{locked_val:.3f}")
                    scale.config(state="disabled")
                    entry.config(state="disabled", disabledforeground=GREY)
            cmds_touch = [
                f"ros2 param set /test_unity_p1 force_target 1.0",
                f"ros2 param set /test_unity_p1 force_wrench 10.0",
                f"ros2 param set /test_unity_p1 offset 0.050",
            ]
            def run_touch():
                for c in cmds_touch:
                    try:
                        subprocess.run(c, shell=True, capture_output=True, timeout=5)
                    except subprocess.TimeoutExpired:
                        pass
            threading.Thread(target=run_touch, daemon=True).start()
            self._confirmed_params['force_target'] = 1.0
            self._confirmed_params['force_wrench'] = 10.0
            self._confirmed_params['offset'] = 0.05
        else:
            print(f"[DEBUG] Passage en Push/Punch — _pre_touch_values à restaurer : {self._pre_touch_values}")
            for lbl in TOUCH_LOCKED:
                if lbl in self._slider_widgets:
                    scale, entry, entry_var, var = self._slider_widgets[lbl]
                    scale.config(state="normal")
                    entry.config(state="normal")
                    if lbl in self._pre_touch_values:
                        var.set(self._pre_touch_values[lbl])
                        entry_var.set(f"{self._pre_touch_values[lbl]:.3f}")
            if hasattr(self, '_confirm_status') and self._pre_touch_values:
                vals = {
                    'force_target': self._pre_touch_values.get('Force cible (N)', self._confirmed_params['force_target']),
                    'force_wrench': self._pre_touch_values.get('Force wrench (N)', self._confirmed_params['force_wrench']),
                    'offset':       self._pre_touch_values.get('Offset pré-P1 (m)', self._confirmed_params['offset']),
                }
                cmds_restore = [f"ros2 param set /test_unity_p1 {k} {v:.3f}" for k, v in vals.items()]
                def run_restore():
                    for c in cmds_restore:
                        try:
                            subprocess.run(c, shell=True, capture_output=True, timeout=5)
                        except subprocess.TimeoutExpired:
                            pass
                threading.Thread(target=run_restore, daemon=True).start()
                self._confirmed_params['force_target'] = vals['force_target']
                self._confirmed_params['force_wrench'] = vals['force_wrench']
                self._confirmed_params['offset']       = vals['offset']
                self._pre_touch_values = {}

    def _do_confirm(self):
        candidates = {
            'force_target': self.force_target.get(),
            'force_wrench': self.force_wrench.get(),
            'force_max':    self.force_max.get(),
            'offset':       self.offset_var.get(),
            'timeout':      self.timeout_var.get(),
            'hold_time':    self.hold_time_var.get(),
        }
        cmds = []
        for key, val in candidates.items():
            if abs(val - self._confirmed_params[key]) > 0.001:
                cmds.append(f"ros2 param set /test_unity_p1 {key} {val:.3f}")
                self._confirmed_params[key] = val

        def run():
            for cmd in cmds:
                try:
                    subprocess.run(cmd, shell=True, capture_output=True, timeout=5)
                except subprocess.TimeoutExpired:
                    pass
            self.after(0, lambda: self._confirm_status.config(
                text="✅ Paramètres envoyés", fg="#1a7a3c"))
        self._confirm_status.config(text="⏳ Envoi des paramètres...", fg="#b87000")
        threading.Thread(target=run, daemon=True).start()

    def _do_confirm_forced(self):
        defaults = {
            'force_target': 10.0,
            'force_wrench': 50.0,
            'force_max':    200.0,
            'offset':        0.001,
            'timeout':      30.0,
            'hold_time':     0.0,
        }
        cmds = []
        for key, val in self._confirmed_params.items():
            if abs(val - defaults[key]) > 0.001:
                cmds.append(f"ros2 param set /test_unity_p1 {key} {val:.3f}")
        def run():
            for cmd in cmds:
                try:
                    subprocess.run(cmd, shell=True, capture_output=True, timeout=5)
                except subprocess.TimeoutExpired:
                    pass
        threading.Thread(target=run, daemon=True).start()

    def _do_start(self):
        if self.ros_running:
            self._set_status("⚠️  Nœuds déjà lancés.", YELLOW)
            return
        self._status_stop.clear()
        self._set_status("⏳ Lancement des nœuds ROS2...", YELLOW)
        self._set_indicator("ros", "pending")

        def run():
            for label, cmd in zip(CMD_LABELS, CMDS):
                self.after(0, lambda l=label: self._set_status(f"⏳ Lancement : {l}...", YELLOW))
                proc = subprocess.Popen(cmd, shell=True,
                                        stdout=subprocess.PIPE,
                                        stderr=subprocess.STDOUT,
                                        start_new_session=True,
                                        text=True)
                self.processes[label] = proc
                threading.Thread(
                    target=self._stream_logs,
                    args=(proc, label), daemon=True).start()
                time.sleep(1.5)
            self.ros_running = True
            self.after(0, self._on_ros_started)

        threading.Thread(target=run, daemon=True).start()

    def _on_ros_started(self):
        self._set_indicator("ros",   "on")
        self._set_indicator("robot", "on")
        self._btn_play.config(state="normal", bg=BTN_BLUE)

        # Ajouté le 18/05
        self._btn_reset_anim.config(state="normal", bg=BTN_BLUE)

        self._btn_cal.config(state="normal")
        for btn in self._scen_btns.values():
            btn.config(state="normal")
        self._btn_confirm.config(state="normal")

        for lbl, (scale, entry, entry_var, var) in self._slider_widgets.items():
            if self.scenario_var.get() == "Touch" and lbl in TOUCH_LOCKED:
                continue
            scale.config(state="normal")
            entry.config(state="normal")

        self._btn_start.config(state="disabled")
        self._btn_stop.config(state="normal")
        self._btn_reset.config(state="normal")

        self._set_status("✅ ROS2 prêt — Mettre le casque puis appuyer PLAY.", GREEN)
        self._status_stop.clear()
        self._status_thread = threading.Thread(target=self._listen_status, daemon=True)
        self._abort_thread = threading.Thread(target=self._listen_abort, daemon=True)
        self._abort_thread.start()
        self._status_thread.start()

        self._do_confirm_forced()
        if self.scenario_var.get() == "Touch":
            self._select_scenario("Touch")

    def _do_play(self):
        cmd = 'ros2 service call /start_session std_srvs/srv/Trigger'
        def run():
            try:
                subprocess.run(cmd, shell=True, capture_output=True, timeout=5)
            except subprocess.TimeoutExpired:
                pass
        threading.Thread(target=run, daemon=True).start()
        self.session_active = True
        self._btn_play.config(state="disabled", bg=GREY)
        self._set_indicator("unity", "on")
        self._set_indicator("session", "on")
        self._set_status(f"🎮 Poussée en cours — Scénario : {self.scenario_var.get()}", BTN_BLUE)

    # Ajouté le 18/05
    def _do_reset_animation(self):
        cmd = 'ros2 service call /reset_animation std_srvs/srv/Trigger'
        def run():
            try:
                subprocess.run(cmd, shell=True, capture_output=True, timeout=5)
            except subprocess.TimeoutExpired:
                pass
        threading.Thread(target=run, daemon=True).start()

    def _do_stop(self):
        self._status_stop.set()
        self._ros2_publish(TOPIC_ABORT, "ABORT depuis IHM")
        self.session_active = False
        self._set_indicator("session", "off")
        self._set_status("⛔ Arrêt en cours...", BTN_RED)

        def kill():
            for label, proc in self.processes.items():
                try:
                    os.killpg(os.getpgid(proc.pid), signal.SIGINT)
                except:
                    pass
            time.sleep(1.0)
            for label, proc in self.processes.items():
                try:
                    os.killpg(os.getpgid(proc.pid), signal.SIGKILL)
                except:
                    pass
            subprocess.run("pkill -9 -f motion_manager_node2", shell=True)
            subprocess.run("pkill -9 -f ur_safety_monitor", shell=True)
            subprocess.run("pkill -9 -f ros2_control_node", shell=True)
            subprocess.run("pkill -9 -f ros_tcp_endpoint", shell=True)
            subprocess.run("pkill -9 -f 'param set'", shell=True)
            subprocess.run("pkill -9 -f 'service call'", shell=True)
            self.processes.clear()
            self.ros_running = False
            self.after(0, self._on_ros_stopped)

        threading.Thread(target=kill, daemon=True).start()

    def _on_ros_stopped(self):
        self._set_indicator("ros",   "off")
        self._set_indicator("robot", "off")
        self._set_indicator("unity", "off")
        self._btn_play.config(state="disabled", bg=GREY)
        # Ajouté le 18/05
        self._btn_reset_anim.config(state="disabled", bg=GREY)
        self._btn_cal.config(state="disabled")
        for btn in self._scen_btns.values():
            btn.config(state="disabled")
        self._btn_confirm.config(state="disabled")
        self._btn_stop.config(state="disabled")
        self._btn_reset.config(state="disabled")

        for lbl, (scale, entry, entry_var, var) in self._slider_widgets.items():
            scale.config(state="disabled")
            entry.config(state="disabled")

        self._btn_start.config(state="normal")
        self._set_status("🔴 Nœuds arrêtés — Appuyez sur DÉMARRER pour relancer.", GREY)

    def _do_reset_params(self):
        defaults = {
            'Force cible (N)':   10.0,
            'Force wrench (N)':  50.0,
            'Force max (N)':     200.0,
            'Offset pré-P1 (m)': 0.001,
            'Timeout (s)':       30.0,
            'Maintien (s)':      0.0,
        }
        touch_mode = self.scenario_var.get() == "Touch"
        for lbl, val in defaults.items():
            if touch_mode and lbl in TOUCH_LOCKED:
                continue
            if lbl in self._slider_widgets:
                scale, entry, entry_var, var = self._slider_widgets[lbl]
                var.set(val)
                entry_var.set(f"{val:.3f}")

    # ══════════════════════════════════════════
    #  ÉCOUTE /masters/status
    # ══════════════════════════════════════════
    def _listen_status(self):
        proc = subprocess.Popen(
            "ros2 topic echo /masters/status std_msgs/msg/String",
            shell=True, stdout=subprocess.PIPE,
            stderr=subprocess.DEVNULL, text=True,
            start_new_session=True
        )
        self.processes["status_listener"] = proc
        for line in proc.stdout:
            if self._status_stop.is_set():
                break
            line = line.strip()
            if "data:" not in line:
                continue
            data = line.split("data:")[-1].strip().strip("'\"")
            if data == "ready":
                self.session_active = False
                self.after(0, self._on_status_ready)
            elif data == "aborted":
                self.session_active = False
                self.after(0, self._on_status_aborted)
            elif data == "waiting":
                self.after(0, self._on_status_waiting)
            elif data == "error":
                self.after(0, self._on_status_error)
            elif data == "restarting":
                self.after(0, self._on_status_restarting)
            elif data == "aborted_norm":
                self.session_active = False
                self.after(0, self._on_status_aborted_norm)
            elif data == "restarted":
                self.after(0, self._on_status_restarted)
            elif data == "aborted_singularity":
                self.session_active = False
                self.after(0, self._on_status_aborted_singularity)

    def _listen_abort(self):
        proc = subprocess.Popen(
            "ros2 topic echo /safety_abort std_msgs/msg/String",
            shell=True, stdout=subprocess.PIPE,
            stderr=subprocess.DEVNULL, text=True,
            start_new_session=True
        )
        self.processes["abort_listener"] = proc
        for line in proc.stdout:
            if self._status_stop.is_set():
                break
            line = line.strip()
            if "data:" not in line:
                continue
            if "FORCE LIMIT" in line:
                self.after(0, lambda: self._set_status(
                    "⚠️ Force limite dépassée — Vérifier le robot puis relancer PLAY.", YELLOW))

    def _on_status_ready(self):
        self._btn_play.config(state="normal", bg=BTN_BLUE)
        self._set_indicator("session", "pending")
        self._set_status("✅ Poussée terminée — Prêt pour le prochain PLAY.", GREEN)
        if self.scenario_var.get() != "Touch":
            self._select_scenario(self.scenario_var.get())

    def _on_status_aborted(self):
        self._btn_play.config(state="normal", bg=BTN_BLUE)
        self._set_indicator("session", "off")
        self._set_status("⚠️ Séquence interrompue — Corriger puis relancer PLAY.", YELLOW)

    def _on_status_waiting(self):
        self._set_indicator("session", "pending")
        self._set_status("⏳ Robot en pre_P1 — En attente du signal start_move...", YELLOW)

    def _on_status_error(self):
        self._set_indicator("session", "off")
        self._set_indicator("robot", "off")
        self._set_status("🔴 Protective Stop détecté ! Reconnecter le robot...", BTN_RED)

    def _on_status_restarting(self):
        self._set_indicator("robot", "pending")
        self._set_status("⏳ Robot en cours de reconnexion...", YELLOW)

    def _on_status_aborted_norm(self):
        self._btn_play.config(state="normal", bg=BTN_BLUE)
        self._set_indicator("session", "off")
        self._set_status("⚠️ Point trop proche de la base — Reculer.", YELLOW)

    def _on_status_restarted(self):
        self._btn_play.config(state="normal", bg=BTN_BLUE)
        self._set_indicator("robot", "on")
        self._set_indicator("session", "off")
        self._set_status("✅ Robot reconnecté — Prêt pour le prochain PLAY.", GREEN)
        self._do_confirm_forced()
        self._select_scenario(self.scenario_var.get())

    def _on_status_aborted_singularity(self):
        self._btn_play.config(state="normal", bg=BTN_BLUE)
        self._set_indicator("session", "off")
        self._set_status("⚠️ Position en singularité — Déplacer le point de contact.", YELLOW)

    # ══════════════════════════════════════════
    #  HELPERS
    # ══════════════════════════════════════════

    def _log(self, label: str, message: str):
        box = self._log_boxes.get(label)
        if not box:
            return
        timestamp = time.strftime("%H:%M:%S")
        box.config(state="normal")
        box.insert("end", f"[{timestamp}] {message}\n")
        box.see("end")
        box.config(state="disabled")

    def _stream_logs(self, proc, label: str):
        for line in proc.stdout:
            if self._status_stop.is_set():
                break
            line = line.strip()
            if line:
                self.after(0, lambda l=line, lb=label: self._log(lb, l))

    def _clear_logs(self):
        for box in self._log_boxes.values():
            box.config(state="normal")
            box.delete("1.0", "end")
            box.config(state="disabled")

    def _col_title(self, parent, text):
        frm = tk.Frame(parent, bg=BG3)
        frm.pack(fill="x")
        tk.Label(frm, text=text,
                 font=("Helvetica", self.sf(14), "bold"),
                 bg=BG3, fg=ACCENT,
                 pady=self.sv(14)).pack(anchor="w", padx=self.s(20))

    def _card_button(self, parent, text, color, fsize, cmd):
        btn = tk.Button(parent, text=text,
                        font=("Helvetica", fsize, "bold"),
                        bg=color, fg=WHITE, relief="flat",
                        activebackground=color, cursor="hand2",
                        command=cmd)
        btn.pack(fill="x", padx=self.s(20), pady=self.sv(4), ipady=self.sv(14))
        return btn

    def _slider_row(self, parent, label, var, mn, mx, row, col):
        cell = tk.Frame(parent, bg=BG2, padx=self.s(8), pady=self.sv(6))
        cell.grid(row=row, column=col, sticky="ew", padx=self.s(6), pady=self.sv(4))
        parent.columnconfigure(col, weight=1)

        hdr = tk.Frame(cell, bg=BG2)
        hdr.pack(fill="x")
        tk.Label(hdr, text=label, font=("Helvetica", self.sf(10)),
                bg=BG2, fg="#2e4057").pack(side="left")

        entry_var = tk.StringVar(value=f"{var.get():.3f}")
        entry = tk.Entry(hdr, textvariable=entry_var,
                        font=("Helvetica", self.sf(10), "bold"),
                        bg="white", fg="#2e4057", insertbackground="#2e4057",
                        relief="flat", width=7)
        entry.pack(side="right")

        def on_slide(v):
            entry_var.set(f"{float(v):.3f}")

        def sync_to_var(*args):
            raw = entry_var.get().replace(',', '.')
            if raw == '' or raw == '-':
                return
            try:
                val = float(raw)
                clamped = max(mn, min(mx, val))
                var.set(clamped)
                if clamped != val:
                    entry_var.set(f"{clamped:.3f}")
            except ValueError:
                pass

        entry.bind('<FocusOut>', lambda e: sync_to_var())
        entry.bind('<Return>', lambda e: sync_to_var())

        scale = ttk.Scale(cell, from_=mn, to=mx, variable=var, orient="horizontal",
                          command=on_slide)
        scale.pack(fill="x")

        self._slider_widgets[label] = (scale, entry, entry_var, var)

    def _set_indicator(self, key, state):
        colors = {"off": GREY, "pending": YELLOW, "on": GREEN}
        self._indicators[key].config(fg=colors.get(state, GREY))

    def _ros2_publish(self, topic, message):
        cmd = f'ros2 topic pub --once {topic} std_msgs/msg/String "{{data: \\"{message}\\"}}"'
        def run():
            try:
                subprocess.run(cmd, shell=True, capture_output=True, timeout=5)
            except subprocess.TimeoutExpired:
                pass
        threading.Thread(target=run, daemon=True).start()

    def _on_close(self):
        self._do_stop()
        self.destroy()


if __name__ == "__main__":
    app = MastersIHM()
    app.mainloop()