#!/usr/bin/env python3
# masters_ihm2.py — IHM MASTERS (plein écran adaptatif)
# Codé le 17/04

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
BG          = "#1a1a2e"
BG2         = "#16213e"
BG3         = "#0f3460"
ACCENT      = "#e94560"
GREEN       = "#00d4aa"
YELLOW      = "#f5a623"
WHITE       = "#f0f0f0"
GREY        = "#555577"
BTN_RED     = "#c0392b"
BTN_GREEN   = "#27ae60"
BTN_BLUE    = "#2980b9"
BTN_ORANGE  = "#e67e22"
BTN_GREY    = "#34495e"

SCENARIO_COLORS = {
    "Push":  "#2980b9",
    "Punch": "#c0392b",
    "Touch": "#27ae60",
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

        # ── Plein écran ──
        self.attributes('-fullscreen', True)
        self.update_idletasks()
        self.W = self.winfo_screenwidth()
        self.H = self.winfo_screenheight()

        # ── Échelles relatives (référence 1920×1080) ──
        self.sx = self.W / 1920
        self.sy = self.H / 1080

        # ── État ──
        self.scenario_var  = tk.StringVar(value="Push")
        self.force_target  = tk.DoubleVar(value=20.0)
        self.force_wrench  = tk.DoubleVar(value=50.0)
        self.force_max     = tk.DoubleVar(value=70.0)
        self.offset_var    = tk.DoubleVar(value=0.1)
        self.timeout_var   = tk.DoubleVar(value=30.0)
        self.hold_time_var = tk.DoubleVar(value=0.5)

        self.processes      = {}
        self.ros_running    = False
        self.session_active = False

        # Ajouté le 20/04 — valeurs de référence pour envoi différentiel
        self._confirmed_params = {
            'force_target': 20.0,
            'force_wrench': 50.0,
            'force_max':    70.0,
            'offset':        0.1,
            'timeout':      30.0,
            'hold_time':     0.5,
        }

        # ── Status listener ──
        self._status_thread = None
        self._status_stop   = threading.Event()

        # Ajouté le 20/04 à 12h25 — dictionnaire des zones de log par nœud
        self._log_boxes = {}

        # Ajouté le 20/04 à 16h30 — références aux widgets sliders/entries pour blocage Touch
        self._slider_widgets = {}  # label → (scale, entry, entry_var)

        self._pre_touch_values = {}  # Ajouté le 21/04

        # ── Build ──
        self._build_header()
        self._build_body()
        self._build_footer()

        # Ajouté le 22/04 — griser les boutons au démarrage
        self._btn_precal.config(state="disabled")
        self._btn_cal.config(state="disabled")
        for btn in self._scen_btns.values():
            btn.config(state="disabled")
        self._btn_confirm.config(state="disabled")

        # Echap pour quitter aussi
        self.bind('<Escape>', lambda e: self._on_close())
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

        tk.Label(frm, text="Système de contrôle robot  —  IRA2 Lab",
                 font=("Helvetica", self.sf(13)),
                 bg=BG3, fg=GREY).pack(side="left")

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

        self._col_title(col, "1 — Calibration")

        tk.Label(col,
            text="Pré-calibration :\nSi le robot a été déplacé\ndepuis la dernière session.",
            font=("Helvetica", self.sf(11)), bg=BG2, fg=GREY,
            justify="left").pack(anchor="w", padx=self.s(20), pady=self.sv(14))

        self._btn_precal = self._card_button(col, "🔧  Pré-calibration",
                                             BTN_GREY, self.sf(14), self._do_precalibration)

        tk.Label(col,
            text="Calibration :\nAligne le robot virtuel\n(casque VR) avec le robot réel.",
            font=("Helvetica", self.sf(11)), bg=BG2, fg=GREY,
            justify="left").pack(anchor="w", padx=self.s(20), pady=self.sv(20))

        self._btn_cal = self._card_button(col, "📐  Calibration",
                                          BTN_BLUE, self.sf(14), self._do_calibration)

        self._cal_status = tk.Label(col, text="",
                                    font=("Helvetica", self.sf(10)),
                                    bg=BG2, fg=YELLOW,
                                    wraplength=self.s(300), justify="left")
        self._cal_status.pack(anchor="w", padx=self.s(20), pady=self.sv(16))

    # ── Colonne 2 : Paramétrage ──
    def _build_col_parametrage(self, parent):
        col = tk.Frame(parent, bg=BG2)
        col.grid(row=0, column=1, sticky="nsew", padx=self.s(8), pady=self.sv(8))

        self._col_title(col, "2 — Paramétrage")

        tk.Label(col, text="Choisir le scénario :",
                 font=("Helvetica", self.sf(12), "bold"),
                 bg=BG2, fg=WHITE).pack(anchor="w", padx=self.s(20), pady=(self.sv(10), self.sv(4)))

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
        self._select_scenario("Push")

        tk.Frame(col, bg=GREY, height=1).pack(fill="x", padx=self.s(20), pady=self.sv(4))

        tk.Label(col, text="Paramètres :",
                 font=("Helvetica", self.sf(12), "bold"),
                 bg=BG2, fg=WHITE).pack(anchor="w", padx=self.s(20), pady=(self.sv(10), self.sv(4)))

        sliders_frm = tk.Frame(col, bg=BG2)
        sliders_frm.pack(fill="x", padx=self.s(20))
        sliders_frm.columnconfigure(0, weight=1)
        sliders_frm.columnconfigure(1, weight=1)

        params = [
            ("Force cible (N)",   self.force_target,  1.0, 100.0, 1.0),
            ("Force wrench (N)",  self.force_wrench,  1.0, 150.0, 1.0),
            ("Force max (N)",     self.force_max,     1.0, 150.0, 1.0),
            ("Offset pré-P1 (m)", self.offset_var,   0.01,  0.3, 0.01),
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
                                        bg=BG2, fg=YELLOW, wraplength=self.s(500))
        self._confirm_status.pack(pady=self.sv(6))

    # ── Colonne 3 : Contrôle ──
    def _build_col_controle(self, parent):
        col = tk.Frame(parent, bg=BG2)
        col.grid(row=0, column=2, sticky="nsew", padx=self.s(8), pady=self.sv(8))

        self._col_title(col, "3 — Contrôle")

        for i, txt in enumerate([
            "① Lancez les nœuds ROS2.",
            "② Mettez le casque VR.",
            "③ Lancez la simulation.",
        ]):
            tk.Label(col, text=txt, font=("Helvetica", self.sf(11)),
                     bg=BG2, fg=GREY).pack(anchor="w", padx=self.s(20),
                                           pady=(self.sv(10) if i == 0 else 0, 0))

        tk.Frame(col, bg=GREY, height=1).pack(fill="x", padx=self.s(20), pady=self.sv(8))

        self._btn_start = self._card_button(col, "▶  DÉMARRER",
                                            BTN_GREEN, self.sf(16), self._do_start)

        self._node_status = tk.Label(col, text="",
                                     font=("Helvetica", self.sf(9)),
                                     bg=BG2, fg=GREY, justify="left")
        self._node_status.pack(anchor="w", padx=self.s(20), pady=self.sv(4))

        tk.Frame(col, bg=GREY, height=1).pack(fill="x", padx=self.s(20), pady=self.sv(8))

        self._btn_play = self._card_button(col, "🎮  PLAY",
                                           GREY, self.sf(16), self._do_play)
        self._btn_play.config(state="disabled")

        tk.Frame(col, bg=GREY, height=1).pack(fill="x", padx=self.s(20), pady=self.sv(8))

        self._btn_stop = self._card_button(col, "⛔  STOP",
                                           BTN_RED, self.sf(16), self._do_stop)

        self._ctrl_status = tk.Label(col, text="",
                                     font=("Helvetica", self.sf(10)),
                                     bg=BG2, fg=YELLOW,
                                     wraplength=self.s(280), justify="left")
        self._ctrl_status.pack(padx=self.s(20), pady=self.sv(8))

        # Ajouté le 20/04 à 12h25 — Zone de logs avec onglets
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
        style.map("TNotebook.Tab", background=[("selected", BG)])

        self._notebook = ttk.Notebook(col)
        self._notebook.pack(fill="both", expand=True, padx=self.s(20), pady=self.sv(4))

        for label in CMD_LABELS:
            frame = tk.Frame(self._notebook, bg=BG)
            self._notebook.add(frame, text=label)
            box = tk.Text(frame,
                          font=("Courier", self.sf(8)),
                          bg=BG, fg=GREEN,
                          relief="flat",
                          state="disabled",
                          wrap="word")
            box.pack(fill="both", expand=True)
            self._log_boxes[label] = box

    # ══════════════════════════════════════════
    #  FOOTER
    # ══════════════════════════════════════════
    def _build_footer(self):
        frm = tk.Frame(self, bg=BG3, height=self.sv(46))
        frm.pack(fill="x", side="bottom")
        frm.pack_propagate(False)

        tk.Label(frm, text="IRA2 — IBISC Lab — Université d'Évry Paris-Saclay",
                 font=("Helvetica", self.sf(9)), bg=BG3, fg=GREY).pack(side="left", padx=self.s(20))

        tk.Button(frm, text="✕  Quitter",
                  font=("Helvetica", self.sf(9), "bold"),
                  bg=BTN_RED, fg=WHITE, relief="flat",
                  activebackground=BTN_RED, cursor="hand2",
                  command=self._on_close).pack(side="right", padx=self.s(20),
                                               pady=self.sv(8), ipadx=self.s(10))

    # ══════════════════════════════════════════
    #  ACTIONS
    # ══════════════════════════════════════════
    def _do_precalibration(self):
        self._cal_status.config(text="⏳ Pré-calibration envoyée à Unity...", fg=YELLOW)
        cmd = 'ros2 service call /set_scenario masters_msgs/srv/SystemStateService "{command: 0}"'
        threading.Thread(
            target=lambda: subprocess.run(cmd, shell=True, capture_output=True),
            daemon=True).start()
        self.after(1500, lambda: self._cal_status.config(
            text="✅ Pré-calibration lancée.\nAttendre confirmation dans le casque.", fg=GREEN))

    def _do_calibration(self):
        self._cal_status.config(text="⏳ Calibration envoyée à Unity...", fg=YELLOW)
        cmd = 'ros2 service call /set_scenario masters_msgs/srv/SystemStateService "{command: 1}"'
        threading.Thread(
            target=lambda: subprocess.run(cmd, shell=True, capture_output=True),
            daemon=True).start()
        self.after(1500, lambda: self._cal_status.config(
            text="✅ Calibration lancée.\nVérifier l'alignement dans le casque.", fg=GREEN))

    def _select_scenario(self, name):
        self.scenario_var.set(name)
        for n, btn in self._scen_btns.items():
            btn.config(bg=SCENARIO_COLORS[n] if n == name else GREY)
        scen_map = {"Push": 3, "Punch": 2, "Touch": 4}
        scen = scen_map[name]
        cmd = f'ros2 service call /set_scenario masters_msgs/srv/SystemStateService "{{command: {scen}}}"'
        threading.Thread(
            target=lambda: subprocess.run(cmd, shell=True, capture_output=True),
            daemon=True).start()

        # Ajouté le 20/04 à 16h30 — bloquer/débloquer sliders selon le scénario
        if name == "Touch":
            print(f"[DEBUG] Passage en Touch — _pre_touch_values AVANT sauvegarde : {self._pre_touch_values}")
            print(f"[DEBUG] Valeurs actuelles — force_target:{self.force_target.get()}, force_wrench:{self.force_wrench.get()}, offset:{self.offset_var.get()}")

            # Ajouté le 21/04 — sauvegarder avant blocage
            # self._pre_touch_values = {
            #     'Force cible (N)':    self.force_target.get(),
            #     'Force wrench (N)':   self.force_wrench.get(),
            #     'Offset pré-P1 (m)':  self.offset_var.get(),
            # }
            # Ajouté le 21/04 — sauvegarder avant blocage (seulement si pas déjà en Touch)
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
                    entry_var.set(f"{locked_val:.2f}")
                    scale.config(state="disabled")
                    entry.config(state="disabled", disabledforeground=GREY)
            # Ajouté le 21/04 — envoyer les valeurs hardcodées Touch au nœud
            cmds_touch = [
                f"ros2 param set /test_unity_p1 force_target 1.0",
                f"ros2 param set /test_unity_p1 force_wrench 10.0",
                f"ros2 param set /test_unity_p1 offset 0.050",
            ]
            threading.Thread(
                target=lambda: [subprocess.run(c, shell=True, capture_output=True) for c in cmds_touch],
                daemon=True).start()
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
                    # Ajouté le 21/04 — restaurer les valeurs d'avant Touch
                    if lbl in self._pre_touch_values:
                        var.set(self._pre_touch_values[lbl])
                        entry_var.set(f"{self._pre_touch_values[lbl]:.2f}")
            # Ajouté le 21/04 — envoyer automatiquement les valeurs restaurées
            # if hasattr(self, '_confirm_status'):
            #     self._do_confirm()

            # Ajouté le 21/04 — envoyer automatiquement les valeurs restaurées en parallèle
            if hasattr(self, '_confirm_status') and self._pre_touch_values:
                vals = {
                    'force_target': self._pre_touch_values.get('Force cible (N)', self._confirmed_params['force_target']),
                    'force_wrench': self._pre_touch_values.get('Force wrench (N)', self._confirmed_params['force_wrench']),
                    'offset':       self._pre_touch_values.get('Offset pré-P1 (m)', self._confirmed_params['offset']),
                }
                cmds_restore = [f"ros2 param set /test_unity_p1 {k} {v:.3f}" for k, v in vals.items()]
                threading.Thread(
                    target=lambda: [subprocess.run(c, shell=True, capture_output=True) for c in cmds_restore],
                    daemon=True).start()
                self._confirmed_params['force_target'] = vals['force_target']
                self._confirmed_params['force_wrench'] = vals['force_wrench']
                self._confirmed_params['offset']       = vals['offset']

    def _do_confirm(self):
        # Commenté le 20/04
        # cmds = [...]

        # Ajouté le 20/04 — envoi différentiel des paramètres modifiés uniquement
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
                subprocess.run(cmd, shell=True, capture_output=True)
            self.after(0, lambda: self._confirm_status.config(
                text="✅ Paramètres envoyés", fg=GREEN))
        self._confirm_status.config(text="⏳ Envoi des paramètres...", fg=YELLOW)
        threading.Thread(target=run, daemon=True).start()

    # Ajouté le 20/04 — renvoie les derniers paramètres confirmés après Protective Stop
    def _do_confirm_forced(self):
        defaults = {
            'force_target': 20.0,
            'force_wrench': 50.0,
            'force_max':    70.0,
            'offset':        0.1,
            'timeout':      30.0,
            'hold_time':     0.5,
        }
        cmds = []
        for key, val in self._confirmed_params.items():
            if abs(val - defaults[key]) > 0.001:
                cmds.append(f"ros2 param set /test_unity_p1 {key} {val:.3f}")
        def run():
            for cmd in cmds:
                subprocess.run(cmd, shell=True, capture_output=True)
        threading.Thread(target=run, daemon=True).start()

    def _do_start(self):
        if self.ros_running:
            self._ctrl_status.config(text="⚠️  Nœuds déjà lancés.", fg=YELLOW)
            return
        self._status_stop.clear()
        self._ctrl_status.config(text="⏳ Lancement des nœuds ROS2...", fg=YELLOW)
        self._set_indicator("ros", "pending")

        # Ajouté le 20/04 à 12h25 — stream stdout de chaque nœud vers son onglet
        def run():
            for label, cmd in zip(CMD_LABELS, CMDS):
                self.after(0, lambda l=label: self._node_status.config(
                    text=f"⏳ Lancement : {l}...", fg=YELLOW))
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
        self._node_status.config(text="✅ 4 nœuds actifs.", fg=GREEN)
        self._btn_play.config(state="normal", bg=BTN_BLUE)

        self._btn_precal.config(state="normal")
        self._btn_cal.config(state="normal")
        for btn in self._scen_btns.values():
            btn.config(state="normal")
        self._btn_confirm.config(state="normal")

        self._ctrl_status.config(
            text="✅ ROS2 prêt.\nMettez le casque puis appuyez PLAY.", fg=GREEN)
        self._status_stop.clear()
        self._status_thread = threading.Thread(target=self._listen_status, daemon=True)
        self._status_thread.start()

    # def _do_play(self):
    #     scen_map = {"Push": 3, "Punch": 2, "Touch": 4}
    #     scen = scen_map[self.scenario_var.get()]
    #     # self._ros2_publish(TOPIC_COMMAND, f"play:{scen}")

    #     # Ajouté le 21/04 — publication répétée pour fiabilité
    #     # cmd = f'ros2 topic pub -r 10 --times 5 {TOPIC_COMMAND} std_msgs/msg/String "{{data: \\"play:{scen}\\"}}"'
    #     # threading.Thread(
    #     #     target=lambda: subprocess.run(cmd, shell=True, capture_output=True),
    #     #     daemon=True).start()
        
    #     # Ajouté le 21/04 — appel service app_control au lieu de topic
    #     cmd = f'ros2 service call /app_control masters_msgs/srv/AppControlService "{{command: 0}}"'
    #     threading.Thread(
    #         target=lambda: subprocess.run(cmd, shell=True, capture_output=True),
    #         daemon=True).start()

    #     self.session_active = True
    #     self._btn_play.config(state="disabled", bg=GREY)
    #     self._set_indicator("unity",   "on")
    #     self._set_indicator("session", "on")
    #     self._ctrl_status.config(
    #         text=f"🎮 Poussée en cours...\nScénario : {self.scenario_var.get()}", fg=GREEN)
        
    def _do_play(self):
        cmd = 'ros2 service call /start_session std_srvs/srv/Trigger'
        threading.Thread(target=lambda: subprocess.run(cmd, shell=True, capture_output=True),daemon=True).start()
        self.session_active = True
        self._btn_play.config(state="disabled", bg=GREY)
        self._set_indicator("unity", "on")
        self._set_indicator("session", "on")
        self._ctrl_status.config(
            text=f"🎮 Poussée en cours...\nScénario : {self.scenario_var.get()}", fg=GREEN)

    def _do_stop(self):
        self._status_stop.set()
        self._ros2_publish(TOPIC_ABORT, "ABORT depuis IHM")
        self.session_active = False
        self._set_indicator("session", "off")
        self._ctrl_status.config(text="⛔ Arrêt en cours...", fg=ACCENT)

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
            self.processes.clear()
            self.ros_running = False
            self.after(0, self._on_ros_stopped)

        threading.Thread(target=kill, daemon=True).start()

    def _on_ros_stopped(self):
        self._set_indicator("ros",   "off")
        self._set_indicator("robot", "off")
        self._set_indicator("unity", "off")
        self._node_status.config(text="")
        self._btn_play.config(state="disabled", bg=GREY)

        self._btn_precal.config(state="disabled")
        self._btn_cal.config(state="disabled")
        for btn in self._scen_btns.values():
            btn.config(state="disabled")
        self._btn_confirm.config(state="disabled")

        self._ctrl_status.config(text="🔴 Nœuds arrêtés.", fg=ACCENT)

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

    def _on_status_ready(self):
        self._btn_play.config(state="normal", bg=BTN_BLUE)
        self._set_indicator("session", "pending")
        self._ctrl_status.config(
            text="✅ Poussée terminée.\nPrêt pour le prochain PLAY.", fg=GREEN)
        
        #self._select_scenario(self.scenario_var.get())
        # Ajouté le 21/04 — ne pas écraser _pre_touch_values si scénario Touch
        if self.scenario_var.get() != "Touch":
            self._select_scenario(self.scenario_var.get())

    def _on_status_aborted(self):
        self._btn_play.config(state="normal", bg=BTN_BLUE)
        self._set_indicator("session", "off")
        self._ctrl_status.config(
            text="⚠️ Séquence interrompue.\nCorrigez puis appuyez PLAY.", fg=YELLOW)

    def _on_status_waiting(self):
        self._set_indicator("session", "pending")
        self._ctrl_status.config(
            text="⏳ Robot en pre_P1.\nEn attente du signal /start_move...", fg=YELLOW)

    def _on_status_error(self):
        self._set_indicator("session", "off")
        self._set_indicator("robot", "off")
        self._ctrl_status.config(
            text="🔴 Protective Stop détecté !\nReconnecter le robot...", fg=ACCENT)

    def _on_status_restarting(self):
        self._set_indicator("robot", "pending")
        # self._btn_play.config(state="normal", bg=BTN_BLUE)
        self._ctrl_status.config(
            text="⏳ Robot en cours de reconnexion...", fg=YELLOW)

    def _on_status_aborted_norm(self):
        self._btn_play.config(state="normal", bg=BTN_BLUE)
        self._set_indicator("session", "off")
        self._ctrl_status.config(
            text="⚠️ Point trop proche de la base.\nChoisissez une autre cible.", fg=YELLOW)

    def _on_status_restarted(self):
        self._btn_play.config(state="normal", bg=BTN_BLUE)
        self._set_indicator("robot", "on")
        self._set_indicator("session", "off")
        self._ctrl_status.config(
            text="✅ Robot reconnecté.\nPrêt pour le prochain PLAY.", fg=GREEN)
        self._do_confirm_forced()
        self._select_scenario(self.scenario_var.get())  # Ajouté le 21/04

    # ══════════════════════════════════════════
    #  HELPERS
    # ══════════════════════════════════════════

    # Ajouté le 20/04 à 12h25
    def _log(self, label: str, message: str):
        box = self._log_boxes.get(label)
        if not box:
            return
        timestamp = time.strftime("%H:%M:%S")
        box.config(state="normal")
        box.insert("end", f"[{timestamp}] {message}\n")
        box.see("end")
        box.config(state="disabled")

    # Ajouté le 20/04 à 12h25
    def _stream_logs(self, proc, label: str):
        for line in proc.stdout:
            if self._status_stop.is_set():
                break
            line = line.strip()
            if line:
                self.after(0, lambda l=line, lb=label: self._log(lb, l))

    # Ajouté le 20/04 à 12h25
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
                bg=BG2, fg=WHITE).pack(side="left")

        entry_var = tk.StringVar(value=f"{var.get():.2f}")
        entry = tk.Entry(hdr, textvariable=entry_var,
                        font=("Helvetica", self.sf(10), "bold"),
                        bg=BG3, fg=ACCENT, insertbackground=WHITE,
                        relief="flat", width=6)
        entry.pack(side="right")

        def on_slide(v):
            entry_var.set(f"{float(v):.2f}")

        def sync_to_var(*args):
            raw = entry_var.get().replace(',', '.')
            if raw == '' or raw == '-':
                return
            try:
                val = float(raw)
                val = max(mn, min(mx, val))
                var.set(val)
            except ValueError:
                pass

        entry_var.trace_add('write', sync_to_var)

        scale = ttk.Scale(cell, from_=mn, to=mx, variable=var, orient="horizontal",
                          command=on_slide)
        scale.pack(fill="x")

        # Ajouté le 20/04 à 16h30 — stocker références pour blocage Touch
        self._slider_widgets[label] = (scale, entry, entry_var, var)

    def _set_indicator(self, key, state):
        colors = {"off": GREY, "pending": YELLOW, "on": GREEN}
        self._indicators[key].config(fg=colors.get(state, GREY))

    def _ros2_publish(self, topic, message):
        cmd = f'ros2 topic pub --once {topic} std_msgs/msg/String "{{data: \\"{message}\\"}}"'
        threading.Thread(
            target=lambda: subprocess.run(cmd, shell=True, capture_output=True),
            daemon=True).start()

    def _on_close(self):
        self._do_stop()
        time.sleep(2.0)
        self.destroy()


if __name__ == "__main__":
    app = MastersIHM()
    app.mainloop()