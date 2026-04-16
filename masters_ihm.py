# NOUVELLE VERSION AVEC PARAMETRES 08/04 à 16h30

#!/usr/bin/env python3
"""
IHM Tkinter - Projet Force Control UR3e (Ali/Fouad)
IBISC Lab - IRA2 Team
Dara - 2026
"""

import tkinter as tk
from tkinter import ttk, scrolledtext, messagebox
import subprocess
import threading
import signal
import os
import time
import yaml
import rtde_control as rtde_ctrl
import socket #Ajouté le 08/04 à 13h30

# ─────────────────────────────────────────────
# CONFIG
# ─────────────────────────────────────────────
ROBOT_IP   = "192.168.1.101"
WS_PATH    = os.path.expanduser("~/ira2_ws")
SOURCE_CMD = f"source {WS_PATH}/install/setup.bash && "
POINTS_YAML = os.path.join(WS_PATH, "points.yaml")

NODE_ORDER = ["teach_node", "ur_driver", "safety_monitor", "force_controller", "motion_manager"]

NODES = {
    "ur_driver": {
        "label": "UR Driver",
        "cmd": f"ros2 launch ur_robot_driver ur_control.launch.py ur_type:=ur3e robot_ip:={ROBOT_IP} launch_rviz:=false",
        "desc": "Driver UR3e — lancer en premier",
        "color": "#4A9EFF",
        "icon": "🔌",
    },
    "safety_monitor": {
        "label": "Safety Monitor",
        "cmd": "ros2 run ur_safety_monitor safety_monitor_node",
        "desc": "Watchdog — surveille F_max et timeout capteur",
        "color": "#FF6B35",
        "icon": "🛡",
    },
    "force_controller": {
        "label": "Force Controller",
        "cmd": "ros2 run ur_force_controller force_controller_node",
        "desc": "FSM force — attend /motion_done pour démarrer",
        "color": "#A78BFA",
        "icon": "⚙",
    },
    "motion_manager": {
        "label": "Motion Manager",
        "cmd": "ros2 run ur_motion_manager motion_manager_node",
        "desc": "Approche P1 auto → publie /motion_done",
        "color": "#34D399",
        "icon": "🤖",
    },
    "teach_node": {
        "label": "Teach Node",
        "cmd": "ros2 run ur_motion_manager teach_node",
        "desc": "Enseignement P1/P2 — terminal interactif",
        "color": "#FBBF24",
        "icon": "✏",
        "interactive": True,
    },
}

# ─────────────────────────────────────────────
# THÈME
# ─────────────────────────────────────────────
BG        = "#0F1117"
BG2       = "#1A1D27"
BG3       = "#22263A"
BG_SEL    = "#2A2F45"
BORDER    = "#2E3250"
TXT       = "#E2E8F0"
TXT_DIM   = "#64748B"
RED       = "#EF4444"
GREEN     = "#22C55E"
YELLOW    = "#EAB308"
ORANGE    = "#F97316"
FONT_MONO = ("Consolas", 9)
FONT_UI   = ("Segoe UI", 10)
FONT_BIG  = ("Segoe UI", 11, "bold")


# ─────────────────────────────────────────────
# PROCESS MANAGER
# ─────────────────────────────────────────────
class ProcessManager:
    def __init__(self):
        self.procs = {}

    def start(self, key, cmd, log_cb):
        if key in self.procs and self.procs[key].poll() is None:
            log_cb(key, f"[WARN] {key} déjà en cours d'exécution\n", "warn")
            return False
        full_cmd = f"bash -c '{SOURCE_CMD} {cmd}'"
        try:
            proc = subprocess.Popen(
                full_cmd, shell=True,
                stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                text=True, bufsize=1,
                preexec_fn=os.setsid,
                env={**os.environ, "PYTHONUNBUFFERED": "1"},
            )
            self.procs[key] = proc
            threading.Thread(
                target=self._read_output,
                args=(proc, log_cb, key), daemon=True,
            ).start()
            log_cb(key, f"[START] {key} PID={proc.pid}\n", "info")
            return True
        except Exception as e:
            log_cb(key, f"[ERROR] Impossible de lancer {key}: {e}\n", "error")
            return False

    def stop(self, key, log_cb):
        proc = self.procs.get(key)
        if proc is None or proc.poll() is not None:
            log_cb(key, f"[INFO] {key} n'est pas en cours d'exécution\n", "info")
            return
        try:
            os.killpg(os.getpgid(proc.pid), signal.SIGTERM)
            proc.wait(timeout=3)
        except Exception:
            try:
                os.killpg(os.getpgid(proc.pid), signal.SIGKILL)
            except Exception:
                pass
        del self.procs[key]
        log_cb(key, f"[STOP] {key} arrêté\n", "warn")

    def is_running(self, key):
        p = self.procs.get(key)
        return p is not None and p.poll() is None

    def stop_all(self, log_cb):
        for key in list(self.procs.keys()):
            self.stop(key, log_cb)

    def _read_output(self, proc, log_cb, key):
        for line in proc.stdout:
            tag = (
                "error"   if any(w in line.lower() for w in ["error", "fatal", "abort", "exception"]) else
                "warn"    if any(w in line.lower() for w in ["warn", "safety", "limit", "protective"]) else
                "success" if any(w in line.lower() for w in ["ready", "active", "done", "bias ready", "start"]) else
                "normal"
            )
            log_cb(key, line, tag)
        log_cb(key, f"[END] {key} terminé\n", "warn")

    #Ajouté le 08/04 à 13h30
    def _dashboard_play(self, log_cb):
        """Envoie la commande play via socket dashboard port 29999."""
        try:
            s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            s.settimeout(5)
            s.connect((ROBOT_IP, 29999))
            s.recv(1024)
            s.send(b'play\n')
            response = s.recv(1024).decode()
            s.close()
            # self._log("all", f"[DASHBOARD] play → {response.strip()}\n", "success")
            log_cb("all", f"[DASHBOARD] play → {response.strip()}\n", "success")  # ← ici
            return True
        except Exception as e:
            # self._log("all", f"[DASHBOARD] Erreur play : {e}\n", "error")
            log_cb("all", f"[DASHBOARD] Erreur play : {e}\n", "error")            # ← et ici
            return False

# ─────────────────────────────────────────────
# IHM PRINCIPALE
# ─────────────────────────────────────────────
class ForceControlIHM(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("Masters IHM — UR3e @ IBISC")
        self.configure(bg=BG)
        self.geometry("1150x800")
        self.minsize(900, 620)
        self.resizable(True, True)

        self.pm = ProcessManager()
        self.node_cards   = {}   # key → Frame carte
        self.node_btns    = {}   # key → (start_btn, stop_btn)
        self.status_dots  = {}   # key → Label dot
        self.log_boxes    = {}   # key → ScrolledText  (+ "all")
        self.selected_key = "all"

        self._abort_banner_visible = False
        self._poll_id = None

        self._build_ui()
        self._poll_status()
        self.protocol("WM_DELETE_WINDOW", self._on_close)

    # ══════════════════════════════════════════
    # CONSTRUCTION UI
    # ══════════════════════════════════════════
    def _build_ui(self):
        # ── HEADER ──
        hdr = tk.Frame(self, bg=BG, pady=8, padx=16)
        hdr.pack(fill="x")
        tk.Label(hdr, text="⚡ MASTERS IHM", font=("Segoe UI", 16, "bold"),
                 bg=BG, fg=TXT).pack(side="left")
        tk.Label(hdr, text=f"UR3e  •  {ROBOT_IP}  •  IBISC IRA2",
                 font=FONT_UI, bg=BG, fg=TXT_DIM).pack(side="left", padx=16)
        tk.Button(hdr, text="⛔  STOP ALL", font=FONT_BIG,
                  bg=RED, fg="white", activebackground="#B91C1C",
                  relief="flat", padx=14, pady=6,
                  command=self._stop_all).pack(side="right")

        tk.Button(hdr, text="🔄  Relancer", font=FONT_BIG,
                  bg="#F97316", fg="white", activebackground="#C2410C",
                  relief="flat", padx=14, pady=6,
                  command=self._relancer).pack(side="right", padx=(0, 8))

        tk.Button(hdr, text="▶▶  Lancer", font=FONT_BIG,
                  bg=GREEN, fg="white", activebackground="#15803D",
                  relief="flat", padx=14, pady=6,
                  command=self._lancer_sequence).pack(side="right", padx=(0, 8))

        tk.Frame(self, bg=BORDER, height=1).pack(fill="x")

        # ── ABORT BANNER ──
        self._abort_frame = tk.Frame(self, bg="#7F1D1D", pady=5)
        self._abort_label = tk.Label(
            self._abort_frame, text="⚠  SAFETY ABORT  ⚠",
            font=("Segoe UI", 12, "bold"), bg="#7F1D1D", fg="#FCA5A5")
        self._abort_label.pack()

        # ── CORPS ──
        body = tk.Frame(self, bg=BG)
        body.pack(fill="both", expand=True, padx=10, pady=8)

        # Colonne gauche
        left = tk.Frame(body, bg=BG, width=360)
        left.pack(side="left", fill="y", padx=(0, 8))
        left.pack_propagate(False)
        self._build_left(left)

        # Colonne droite
        right = tk.Frame(body, bg=BG)
        right.pack(side="left", fill="both", expand=True)
        self._build_right(right)

        # ── STATUS BAR ──
        sb = tk.Frame(self, bg=BG3, pady=3)
        sb.pack(fill="x", side="bottom")
        self._statusbar = tk.Label(sb, text="Prêt.", font=FONT_MONO,
                                   bg=BG3, fg=TXT_DIM, anchor="w", padx=8)
        self._statusbar.pack(fill="x")

    # ── COLONNE GAUCHE ──────────────────────────
    def _build_left(self, parent):
        # Scrollable
        canvas = tk.Canvas(parent, bg=BG, highlightthickness=0)
        sb = tk.Scrollbar(parent, orient="vertical", command=canvas.yview)
        canvas.configure(yscrollcommand=sb.set)
        sb.pack(side="right", fill="y")
        canvas.pack(side="left", fill="both", expand=True)
        inner = tk.Frame(canvas, bg=BG)
        canvas.create_window((0, 0), window=inner, anchor="nw")
        inner.bind("<Configure>", lambda e: canvas.configure(
            scrollregion=canvas.bbox("all")))

        # Section enseignement
        self._section_lbl(inner, "📐  PHASE 1 — ENSEIGNEMENT")
        self._node_card(inner, "teach_node")

        tk.Frame(inner, bg=BORDER, height=1).pack(fill="x", pady=6)

        # Section exécution
        self._section_lbl(inner, "🚀  PHASE 2 — EXÉCUTION AUTONOME")
        for k in ["ur_driver", "safety_monitor", "force_controller", "motion_manager"]:
            self._node_card(inner, k)

        tk.Frame(inner, bg=BORDER, height=1).pack(fill="x", pady=6)

        # Points YAML
        self._section_lbl(inner, "📁  POINTS.YAML")
        yf = tk.Frame(inner, bg=BG2, padx=10, pady=8)
        yf.pack(fill="x", pady=2)
        self._yaml_lbl = tk.Label(yf, text="—", font=FONT_MONO,
                                   bg=BG2, fg=TXT_DIM, justify="left",
                                   wraplength=300, anchor="w")
        self._yaml_lbl.pack(fill="x")
        tk.Button(yf, text="🔄 Rafraîchir", font=FONT_MONO,
                  bg=BG3, fg=TXT, relief="flat", pady=2,
                  command=self._refresh_yaml).pack(anchor="w", pady=(4, 0))
        self._refresh_yaml()

    def _section_lbl(self, parent, text):
        tk.Label(parent, text=text, font=("Segoe UI", 9, "bold"),
                 bg=BG, fg=TXT_DIM, anchor="w").pack(
                 fill="x", pady=(8, 2), padx=4)

    def _node_card(self, parent, key):
        cfg   = NODES[key]
        color = cfg["color"]
        is_interactive = cfg.get("interactive", False)

        # Cadre cliquable
        card = tk.Frame(parent, bg=BG2, pady=8, padx=8, cursor="hand2")
        card.pack(fill="x", pady=3)
        self.node_cards[key] = card

        # Bande colorée gauche
        band = tk.Frame(card, bg=color, width=4)
        band.pack(side="left", fill="y", padx=(0, 8))

        body = tk.Frame(card, bg=BG2)
        body.pack(side="left", fill="both", expand=True)

        # Titre + dot
        tr = tk.Frame(body, bg=BG2)
        tr.pack(fill="x")
        dot = tk.Label(tr, text="●", font=("Segoe UI", 10), bg=BG2, fg=TXT_DIM)
        dot.pack(side="left")
        self.status_dots[key] = dot
        tk.Label(tr, text=f"{cfg['icon']}  {cfg['label']}",
                 font=FONT_BIG, bg=BG2, fg=TXT).pack(side="left", padx=6)

        # Description
        tk.Label(body, text=cfg["desc"], font=("Segoe UI", 8),
                 bg=BG2, fg=TXT_DIM, anchor="w").pack(fill="x")

        # Boutons
        br = tk.Frame(body, bg=BG2)
        br.pack(fill="x", pady=(4, 0))

        if is_interactive:
            sb_btn = tk.Button(br, text="▶  Ouvrir Terminal",
                               font=FONT_UI, bg=color, fg="white",
                               relief="flat", padx=10, pady=3,
                               command=lambda k=key, c=cfg: self._start_teach(k, c))
        else:
            sb_btn = tk.Button(br, text="▶  Start",
                               font=FONT_UI, bg=color, fg="white",
                               relief="flat", padx=10, pady=3,
                               command=lambda k=key, c=cfg: self._start_node(k, c))
        sb_btn.pack(side="left", padx=(0, 6))

        st_btn = tk.Button(br, text="■  Stop",
                           font=FONT_UI, bg=BG3, fg=TXT,
                           relief="flat", padx=10, pady=3,
                           command=lambda k=key: self._stop_node(k))
        st_btn.pack(side="left")
        self.node_btns[key] = (sb_btn, st_btn)

        # Clic sur la carte → sélection du terminal
        for widget in [card, band, body, tr, dot, br]:
            widget.bind("<Button-1>", lambda e, k=key: self._select_terminal(k))

    # ── COLONNE DROITE ──────────────────────────
    def _build_right(self, parent):
        nb = ttk.Notebook(parent)
        nb.pack(fill="both", expand=True)

        style = ttk.Style()
        style.theme_use("default")
        style.configure("TNotebook",     background=BG,  borderwidth=0)
        style.configure("TNotebook.Tab", background=BG3, foreground=TXT,
                        font=FONT_UI, padding=(12, 5))
        style.map("TNotebook.Tab", background=[("selected", BG2)])

        # ── Onglet Logs ──
        log_frame = tk.Frame(nb, bg=BG2)
        nb.add(log_frame, text="📋  Logs")
        self._build_log_tab(log_frame)

        # ── Onglet Paramètres ──
        param_frame = tk.Frame(nb, bg=BG2)
        nb.add(param_frame, text="⚙  Paramètres")
        self._build_param_tab(param_frame)

        # ── Onglet Guide ──
        help_frame = tk.Frame(nb, bg=BG2)
        nb.add(help_frame, text="❓  Guide")
        self._build_help_tab(help_frame)

    def _build_log_tab(self, parent):
        # Barre du haut : label terminal actif + bouton effacer
        toolbar = tk.Frame(parent, bg=BG2, pady=4)
        toolbar.pack(fill="x", padx=6)

        self._terminal_label = tk.Label(
            toolbar, text="Console — Tous les nodes",
            font=FONT_BIG, bg=BG2, fg=TXT)
        self._terminal_label.pack(side="left")

        tk.Button(toolbar, text="🗑 Effacer", font=FONT_MONO,
                  bg=BG3, fg=TXT, relief="flat", padx=8,
                  command=self._clear_current_log).pack(side="right")

        # Sélecteur rapide de terminal (boutons en haut)
        sel_bar = tk.Frame(parent, bg=BG3, pady=4)
        sel_bar.pack(fill="x", padx=6)

        self._sel_btns = {}
        all_tabs = [("all", "Tous", "#4A9EFF")] + [
            (k, NODES[k]["label"], NODES[k]["color"])
            for k in ["ur_driver", "safety_monitor", "force_controller", "motion_manager"]
        ]
        for key, label, color in all_tabs:
            btn = tk.Button(
                sel_bar, text=label, font=("Segoe UI", 8),
                bg=BG3, fg=TXT_DIM, relief="flat", padx=8, pady=3,
                command=lambda k=key: self._select_terminal(k))
            btn.pack(side="left", padx=2)
            self._sel_btns[key] = btn

        # Conteneur des log boxes (stacked, une seule visible)
        self._log_container = tk.Frame(parent, bg=BG2)
        self._log_container.pack(fill="both", expand=True, padx=6, pady=(0, 6))

        # Créer une log box par node + une "all"
        tags = {
            "normal":  "#CBD5E1",
            "info":    "#60A5FA",
            "warn":    "#FCD34D",
            "error":   "#F87171",
            "success": "#4ADE80",
        }
        for key in ["all"] + list(NODES.keys()):
            box = scrolledtext.ScrolledText(
                self._log_container,
                bg="#0D1017", fg=TXT, font=FONT_MONO,
                relief="flat", bd=0, wrap="word", state="disabled",
                insertbackground=TXT,
            )
            for tag, color in tags.items():
                box.tag_config(tag, foreground=color)
            self.log_boxes[key] = box

        # Afficher "all" par défaut
        self._show_log_box("all")

    def _show_log_box(self, key):
        """Cache toutes les boxes et affiche celle de `key`."""
        for k, box in self.log_boxes.items():
            box.place_forget()

        self.log_boxes[key].place(relx=0, rely=0, relwidth=1, relheight=1)
        self.selected_key = key

        # Mettre à jour le label
        if key == "all":
            self._terminal_label.config(text="Console — Tous les nodes")
        else:
            cfg = NODES[key]
            self._terminal_label.config(
                text=f"Console — {cfg['icon']}  {cfg['label']}",
                fg=cfg["color"])

        # Mettre à jour les boutons sélecteur
        for k, btn in self._sel_btns.items():
            if k == key:
                color = NODES[k]["color"] if k != "all" else "#4A9EFF"
                btn.config(bg=color, fg="white")
            else:
                btn.config(bg=BG3, fg=TXT_DIM)

        # Mettre à jour le highlight des cartes
        for k, card in self.node_cards.items():
            card.config(bg=BG_SEL if k == key else BG2)
            for child in card.winfo_children():
                try:
                    child.config(bg=BG_SEL if k == key else BG2)
                except Exception:
                    pass

    def _select_terminal(self, key):
        self._show_log_box(key)

    def _build_param_tab(self, parent):
        canvas = tk.Canvas(parent, bg=BG2, highlightthickness=0)
        vsb = ttk.Scrollbar(parent, orient="vertical", command=canvas.yview)
        canvas.configure(yscrollcommand=vsb.set)
        vsb.pack(side="right", fill="y")
        canvas.pack(side="left", fill="both", expand=True)
        inner = tk.Frame(canvas, bg=BG2)
        canvas.create_window((0, 0), window=inner, anchor="nw")
        inner.bind("<Configure>", lambda e: canvas.configure(
            scrollregion=canvas.bbox("all")))

        self._param_vars = {}

        params = [
            ("── Force Controller ──", None, None, None),
            ("force_target",      "Force cible (N)",               "20.0", "défaut=20.0 — Intensité de la poussée/frappe"),
            ("force_max",         "Force max sécurité (N)",        "70.0", "défaut=70.0 — Limite avant abort"),
            ("scenario_mode",     "Scénario (0=Push / 1=Punch)",   "0",    "défaut=0 — 0: maintien  |  1: frappe rapide"),
            ("contact_threshold", "Seuil contact (N)",             "0",  "défaut=0 — 0 = frappe directe"),
            ("force_sign",        "Signe (1=Push / -1=Pull)",      "1.0",  "défaut=1.0 — 1.0: pousse  |  -1.0: tire"),
            ("speed_limit_z",     "Vitesse max axe X (m/s)",       "0.50", "défaut=0.5 — Vitesse le long du vecteur"),
            ("damping_factor",    "Amortissement (0..1)",          "0.5",  "défaut=0.5 — Plus élevé = plus lisse"),
            ("gain_scaling",      "Gain (0..2)",                   "2",    "défaut=2 — Plus élevé = plus réactif"),
            ("contact_lost_time", "Temps contact perdu (s)",       "120.0","défaut=120.0 — Retrait si contact perdu"),
            ("settle_time",       "Délai stabilisation (s)",       "0.2",  "défaut=0.2 — Attente avant zéro capteur"),
            ("── Safety Monitor ──", None, None, None),
            ("max_force_allowed", "Force max absolue (N)",         "80.0", "défaut=80.0 — Seuil watchdog indépendant"),
            ("watchdog_timeout",  "Timeout watchdog (s)",          "0.5",  "défaut=0.5 — Silence max avant abort"),
        ]

        tk.Label(inner, text="Éditer puis cliquer Appliquer — mise à jour à chaud",
                 font=FONT_UI, bg=BG2, fg=TXT_DIM, anchor="w").pack(
                 fill="x", padx=14, pady=(10, 4))

        for name, label, default, desc in params:
            if label is None:
                tk.Label(inner, text=name, font=("Segoe UI", 10, "bold"),
                         bg=BG2, fg=TXT_DIM, anchor="w").pack(
                         fill="x", padx=14, pady=(12, 2))
                continue
            f = tk.Frame(inner, bg=BG2)
            f.pack(fill="x", padx=14, pady=2)
            tk.Label(f, text=label, font=FONT_UI, bg=BG2, fg=TXT,
                     width=30, anchor="w").pack(side="left")
            var = tk.StringVar(value=default)
            self._param_vars[name] = var
            tk.Entry(f, textvariable=var, font=FONT_MONO,
                     bg=BG3, fg=TXT, relief="flat", width=10,
                     insertbackground=TXT).pack(side="left", padx=6)
            tk.Label(f, text=desc, font=("Segoe UI", 8),
                     bg=BG2, fg=TXT_DIM, anchor="w").pack(side="left", padx=4)
            #Ajouté le 08/04 à 16h30
            if name == "force_target":
                tk.Button(f, text="✅ Appliquer", font=FONT_MONO,
                        bg="#4A9EFF", fg="white", relief="flat", padx=6,
                        command=lambda: self._apply_params("force")).pack(side="left", padx=4)
        
        # Commenté le 08/04 à 16h30        
        # bf = tk.Frame(inner, bg=BG2)
        # bf.pack(fill="x", padx=14, pady=14)

        # tk.Button(bf, text="✅  Appliquer force_controller",
        #           font=FONT_UI, bg="#4A9EFF", fg="white", relief="flat",
        #           padx=10, pady=5,
        #           command=lambda: self._apply_params("force")).pack(side="left", padx=(0, 8))
        # tk.Button(bf, text="✅  Appliquer safety_monitor",
        #           font=FONT_UI, bg=ORANGE, fg="white", relief="flat",
        #           padx=10, pady=5,
        #           command=lambda: self._apply_params("safety")).pack(side="left")



    def _build_help_tab(self, parent):
        txt = scrolledtext.ScrolledText(parent, bg=BG2, fg=TXT, font=FONT_MONO,
                                         relief="flat", bd=0, wrap="word")
        txt.pack(fill="both", expand=True, padx=10, pady=8)
        guide = """╔══════════════════════════════════════════════════════════════╗
║         GUIDE OPÉRATOIRE — FORCE CONTROL UR3e              ║
╚══════════════════════════════════════════════════════════════╝

PHASE 1 — ENSEIGNEMENT (une seule fois)
────────────────────────────────────────
 1. Cliquer [Ouvrir Terminal] sur Teach Node
 2. Dans le terminal :
    • Robot en freedrive automatique
    • Amener en P1 → [ENTER]
    • Amener en P2 → [ENTER]
    → points.yaml généré dans ~/ira2_ws/

PHASE 2 — EXÉCUTION AUTONOME
─────────────────────────────
 Ordre recommandé :
 1. UR Driver        — driver ROS2 UR3e
 2. Safety Monitor   — watchdog indépendant
 3. Force Controller — FSM (attend /motion_done)
 4. Motion Manager   — approche P1 → déclenche force

TERMINALS PAR NODE
──────────────────
 • Cliquer sur une carte à gauche → affiche son terminal
 • Ou utiliser les boutons en haut de la console
 → Utile pour surveiller quel node est actif après un crash

APRÈS UN PROTECTIVE STOP
─────────────────────────
 Sur Polyscope :
 1. Enable Robot → OK (singularité)
 2. Local → Play URCaps → Remote
 Sur IHM :
 3. Stop Driver → Start Driver
 4. Relancer safety, force, motion dans l'ordre

SCÉNARIOS
─────────
 scenario_mode = 0  →  PUSH (maintien force soutenue)
 scenario_mode = 1  →  PUNCH (frappe + retrait rapide)
 contact_threshold = 0  →  frappe directe sans attendre

AJUSTEMENT EN LIVE
──────────────────
 Onglet Paramètres → modifier → Appliquer
 Ex: ros2 param set /ur_force_controller force_target 15.0
"""
        txt.insert("1.0", guide)
        txt.config(state="disabled")

    # ══════════════════════════════════════════
    # ACTIONS NODES
    # ══════════════════════════════════════════
    def _start_node(self, key, cfg):
        self.pm.start(key, cfg["cmd"], self._log)
        self._set_status(f"Démarrage {cfg['label']}...")
        # Auto-sélection du terminal au démarrage
        self._select_terminal(key)

    def _start_teach(self, key, cfg):
        full_cmd = f"{SOURCE_CMD} {cfg['cmd']}"
        try:
            subprocess.Popen(
                ["bash", "-c",
                 f'xterm -title "Teach Node — P1/P2" -geometry 80x24 '
                 f'-e bash -c "{full_cmd}; echo; echo [DONE] Appuyer Entrée; read"'],
                preexec_fn=os.setsid,
            )
            self._log("teach_node", "[START] teach_node lancé dans xterm\n", "info")
            self._set_status("Teach Node ouvert dans xterm.")
        except FileNotFoundError:
            self._log("teach_node", "[WARN] xterm non trouvé, lancement console...\n", "warn")
            self.pm.start(key, cfg["cmd"], self._log)

    def _stop_node(self, key):
        self.pm.stop(key, self._log)

    def _stop_all(self):
        if messagebox.askyesno("Confirmation", "Arrêter TOUS les nodes ?"):
            self.pm.stop_all(self._log)
            self._set_status("⛔ Tous les nodes arrêtés.")

    #Ajouté le 08/04 à 16h30
    def _build_force_cmd(self):
        params = {
            "force_target":      self._param_vars.get("force_target", tk.StringVar(value="20.0")).get(),
            "force_max":         self._param_vars.get("force_max", tk.StringVar(value="70.0")).get(),
            "scenario_mode":     self._param_vars.get("scenario_mode", tk.StringVar(value="0")).get(),
            "contact_threshold": self._param_vars.get("contact_threshold", tk.StringVar(value="0.0")).get(),
            "force_sign":        self._param_vars.get("force_sign", tk.StringVar(value="1.0")).get(),
            "speed_limit_z":     self._param_vars.get("speed_limit_z", tk.StringVar(value="0.50")).get(),
            "damping_factor":    self._param_vars.get("damping_factor", tk.StringVar(value="0.5")).get(),
            "gain_scaling":      self._param_vars.get("gain_scaling", tk.StringVar(value="2")).get(),
            "contact_lost_time": self._param_vars.get("contact_lost_time", tk.StringVar(value="120.0")).get(),
            "settle_time":       self._param_vars.get("settle_time", tk.StringVar(value="0.2")).get(),
        }
        args = " ".join([f"-p {k}:={v}" for k, v in params.items()])
        return f"ros2 run ur_force_controller force_controller_node --ros-args {args}"

    def _lancer_sequence(self):
        """Lance driver → play → safety → force → motion."""
        self._driver_ready = False
        self._driver_connected = False

        def _run():
            self._log("all", "[LANCER] Démarrage de la séquence...\n", "info")

            # 1. Lancer le driver
            self._log("all", "[LANCER] 1/5 — Lancement UR Driver...\n", "info")
            self.pm.start("ur_driver", NODES["ur_driver"]["cmd"], self._log_and_detect)
            self.after(0, lambda: self._select_terminal("ur_driver"))

            # 2. Attendre que le driver soit initialisé
            self._log("all", "[LANCER] 2/5 — Attente initialisation driver...\n", "info")
            timeout = 30
            elapsed = 0
            while elapsed < timeout and not self._driver_ready:
                time.sleep(1)
                elapsed += 1
            if not self._driver_ready:
                self._log("all", "[LANCER] ❌ Timeout driver\n", "error")
                return
            self._log("all", "[LANCER] ✅ Driver initialisé !\n", "success")

            # 3. Envoyer play via socket dashboard
            self._log("all", "[LANCER] 3/5 — Envoi commande play...\n", "info")
            #if not self._dashboard_play():
            # if not self.pm._dashboard_play():
            if not self.pm._dashboard_play(self._log):
                self._log("all", "[LANCER] ❌ Commande play échouée\n", "error")
                return

            # 4. Attendre Robot connected to reverse interface
            self._log("all", "[LANCER] 4/5 — Attente reverse interface...\n", "info")
            timeout2 = 15
            elapsed2 = 0
            while elapsed2 < timeout2 and not self._driver_connected:
                time.sleep(1)
                elapsed2 += 1
            if not self._driver_connected:
                self._log("all", "[LANCER] ❌ Timeout reverse interface\n", "error")
                return
            self._log("all", "[LANCER] ✅ Robot prêt !\n", "success")
            time.sleep(1)

            # 5. Safety monitor
            self._log("all", "[LANCER] 5/5 — Lancement nodes...\n", "info")
            self.pm.start("safety_monitor", NODES["safety_monitor"]["cmd"], self._log)
            time.sleep(2)
            #self.pm.start("force_controller", NODES["force_controller"]["cmd"], self._log) #Commenté le 08/04 à 16h30
            self.pm.start("force_controller", self._build_force_cmd(), self._log) #Ajouté le 08/04 à 16h30
            time.sleep(2)
            self.pm.start("motion_manager", NODES["motion_manager"]["cmd"], self._log)

            self._log("all", "[LANCER] ✅ Séquence complète !\n", "success")
            self.after(0, lambda: self._set_status("✅ Système lancé"))

        threading.Thread(target=_run, daemon=True).start()

    def _log_and_detect(self, node_key, text, tag="normal"):
        if "process has finished cleanly" in text:
            self._driver_ready = True
        if "Robot connected to reverse interface" in text:
            self._driver_connected = True
        self._log(node_key, text, tag)

    def _relancer(self):
        """Après un crash : play → attendre reverse interface → relance force + motion."""
        self._driver_connected = False

        def _run():
            self._log("all", "[RELANCER] Envoi commande play...\n", "info")
            # if not self._dashboard_play():
            # if not self.pm._dashboard_play():
            if not self.pm._dashboard_play(self._log):
                self._log("all", "[RELANCER] ❌ Commande play échouée\n", "error")
                return

            # Ajouté le 08/04 à 15h45
            # Réabonner le driver à _log_and_detect pour détecter la reconnexion
            if "ur_driver" in self.pm.procs:
                proc = self.pm.procs["ur_driver"]
                threading.Thread(
                    target=self.pm._read_output,
                    args=(proc, self._log_and_detect, "ur_driver"), daemon=True
                ).start()

            # Attendre Robot connected to reverse interface
            self._log("all", "[RELANCER] Attente reverse interface...\n", "info")
            timeout = 15
            elapsed = 0
            while elapsed < timeout and not self._driver_connected:
                time.sleep(0.5)
                elapsed += 0.5
            if not self._driver_connected:
                self._log("all", "[RELANCER] ❌ Timeout reverse interface\n", "error")
                return
            self._log("all", "[RELANCER] ✅ Robot prêt !\n", "success")

            # Commenté le 08/04 à 15h45
            #self._log("all", "[RELANCER] Attente connexion (3s)...\n", "info")
            #time.sleep(3)
            #self._log("all", "[RELANCER] ✅ Robot prêt !\n", "success")

            # Stop + relance force et motion
            self.pm.stop("motion_manager", self._log)
            self.pm.stop("force_controller", self._log)
            time.sleep(0.5)
            #self.pm.start("force_controller", NODES["force_controller"]["cmd"], self._log) #Commenté le 08/04 à 16h30
            self.pm.start("force_controller", self._build_force_cmd(), self._log) #Ajouté le 08/04 à 16h30
            time.sleep(1)
            self.pm.start("motion_manager", NODES["motion_manager"]["cmd"], self._log)

            self._log("all", "[RELANCER] ✅ Relance terminée !\n", "success")
            self.after(0, lambda: self._set_status("✅ Relance effectuée"))

        threading.Thread(target=_run, daemon=True).start()

    # ══════════════════════════════════════════
    # PARAMÈTRES
    # ══════════════════════════════════════════
    def _apply_params(self, target):
        if target == "force":
            node_name = "/ur_force_controller"
            keys = ["force_target", "force_max", "scenario_mode",
                    "contact_threshold", "force_sign", "speed_limit_z",
                    "damping_factor", "gain_scaling", "contact_lost_time", "settle_time"]
        else:
            node_name = "/ur_safety_monitor"
            keys = ["max_force_allowed", "watchdog_timeout"]

        applied = []
        for pname in keys:
            val = self._param_vars.get(pname, tk.StringVar()).get().strip()
            if not val:
                continue
            subprocess.Popen(["bash", "-c",
                f"{SOURCE_CMD} ros2 param set {node_name} {pname} {val}"])
            applied.append(f"{pname}={val}")

        if applied:
            self._log("all", f"[PARAM] {node_name} : {', '.join(applied)}\n", "success")
            self._set_status(f"Paramètres appliqués sur {node_name}")

    # ══════════════════════════════════════════
    # YAML
    # ══════════════════════════════════════════
    def _refresh_yaml(self):
        for p in [POINTS_YAML, os.path.join(os.getcwd(), "points.yaml")]:
            if os.path.exists(p):
                try:
                    with open(p) as f:
                        data = yaml.safe_load(f)
                    p1 = data.get("p1", {}).get("pos", "?")
                    p2 = data.get("p2", {}).get("pos", "?")
                    self._yaml_lbl.config(fg=GREEN,
                        text=f"✅  {os.path.basename(p)}\n"
                             f"P1 = {[round(x, 4) for x in p1]}\n"
                             f"P2 = {[round(x, 4) for x in p2]}")
                    return
                except Exception as e:
                    self._yaml_lbl.config(fg=YELLOW, text=f"⚠  Erreur: {e}")
                    return
        self._yaml_lbl.config(fg=RED,
            text="❌  points.yaml introuvable\n→ Lancer Teach Node d'abord")

    # ══════════════════════════════════════════
    # LOGS
    # ══════════════════════════════════════════
    def _log(self, node_key, text, tag="normal"):
        """Écrit dans la box du node ET dans la box 'all'."""
        def _do():
            ts = time.strftime("%H:%M:%S")
            entry = f"[{ts}] {text}"

            # Box spécifique au node
            if node_key in self.log_boxes:
                box = self.log_boxes[node_key]
                box.config(state="normal")
                box.insert("end", entry, tag)
                box.see("end")
                box.config(state="disabled")

            # Box globale "all" avec préfixe node
            all_box = self.log_boxes["all"]
            all_box.config(state="normal")
            prefix = f"[{NODES[node_key]['label'][:6]}] " if node_key in NODES else ""
            all_box.insert("end", f"[{ts}] {prefix}{text}", tag)
            all_box.see("end")
            all_box.config(state="disabled")

            # Détection abort
            if "abort" in text.lower():
                self._show_abort_banner(text.strip())

        self.after(0, _do)

    def _clear_current_log(self):
        box = self.log_boxes.get(self.selected_key)
        if box:
            box.config(state="normal")
            box.delete("1.0", "end")
            box.config(state="disabled")

    # ══════════════════════════════════════════
    # ABORT BANNER
    # ══════════════════════════════════════════
    def _show_abort_banner(self, reason=""):
        if not self._abort_banner_visible:
            self._abort_banner_visible = True
            self._abort_frame.pack(fill="x")
            self._abort_label.config(text=f"⚠  SAFETY ABORT  —  {reason[:80]}")
            self._blink(4)

    def _blink(self, n):
        if n <= 0:
            return
        c = self._abort_frame.cget("bg")
        nc = "#991B1B" if c == "#7F1D1D" else "#7F1D1D"
        self._abort_frame.config(bg=nc)
        self._abort_label.config(bg=nc)
        self.after(300, lambda: self._blink(n - 1))

    # ══════════════════════════════════════════
    # POLLING STATUT
    # ══════════════════════════════════════════
    def _poll_status(self):
        for key in NODES:
            running = self.pm.is_running(key)
            self.status_dots[key].config(fg=GREEN if running else TXT_DIM)
            sb, st = self.node_btns[key]
            sb.config(state="disabled" if running else "normal")
            st.config(state="normal" if running else "disabled")
        self._poll_id = self.after(1000, self._poll_status)

    def _set_status(self, msg):
        self._statusbar.config(text=msg)

    # ══════════════════════════════════════════
    # FERMETURE
    # ══════════════════════════════════════════
    def _on_close(self):
        running = [k for k in NODES if self.pm.is_running(k)]
        if running:
            if not messagebox.askyesno(
                "Nodes actifs",
                f"{len(running)} node(s) actif(s).\nArrêter avant de quitter ?"
            ):
                return
            self.pm.stop_all(self._log)
            time.sleep(0.5)
        if self._poll_id:
            self.after_cancel(self._poll_id)
        self.destroy()


# ─────────────────────────────────────────────
def main():
    app = ForceControlIHM()
    app.mainloop()

if __name__ == "__main__":
    main()