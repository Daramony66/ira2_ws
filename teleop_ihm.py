#!/usr/bin/env python3
"""
SPHERE Launcher — IHM de lancement rapide des noeuds ROS2
Lancer avec : python3 sphere_launcher.py
"""

import tkinter as tk
from tkinter import scrolledtext
import subprocess
import threading
import os
import signal

# ─── Commandes ───────────────────────────────────────────────────────────────

COMMANDS = {
    "ur_driver": {
        "label": "① UR Robot Driver",
        "cmd": [
            "bash", "-c",
            "source /opt/ros/jazzy/setup.bash && "
            "source ~/ira2_ws/install/setup.bash && "
            "ros2 launch ur_robot_driver ur_control.launch.py "
            "ur_type:=ur3e robot_ip:=192.168.1.101 "
            "use_fake_hardware:=false launch_rviz:=false"
        ],
        "color_on": "#22c55e",
        "color_off": "#166534",
    },
    "ros_tcp": {
        "label": "② ROS TCP Endpoint",
        "cmd": [
            "bash", "-c",
            "source /opt/ros/jazzy/setup.bash && "
            "source ~/ira2_ws/install/setup.bash && "
            "ros2 run ros_tcp_endpoint default_server_endpoint "
            "--ros-args -p ROS_IP:=0.0.0.0"
        ],
        "color_on": "#3b82f6",
        "color_off": "#1e3a5f",
    },
    "haptic": {
        "label": "③ Haptic Control",
        "cmd": [
            "bash", "-c",
            "source /opt/ros/jazzy/setup.bash && "
            "source ~/ira2_ws/install/setup.bash && "
            "ros2 run haptic_teleop haptic_control3"
        ],
        "color_on": "#f59e0b",
        "color_off": "#78350f",
    },
    "haptic_dual": {
        "label": "③' Haptic Dual (test mono-bras)",
        "cmd": [
            "bash", "-c",
            "source /opt/ros/jazzy/setup.bash && "
            "source ~/ira2_ws/install/setup.bash && "
            "ros2 run haptic_teleop haptic_control_dual "
            "--ros-args "
            # "-r /haptic_position:=/expert/haptic_position "
            # "-r /button_pressed:=/expert/button_pressed "
            # "-r /expert/haptic_force:=/haptic_force"

            "-r /expert/haptic_position:=/haptic_position "
            "-r /expert/button_pressed:=/button_pressed "
            "-r /expert/haptic_force:=/haptic_force"
        ],
        "color_on": "#f59e0b",
        "color_off": "#78350f",
    },
    "haptic_dual_full": {
        "label": "③'' Haptic Dual (2 bras)",
        "cmd": [
            "bash", "-c",
            "source /opt/ros/jazzy/setup.bash && "
            "source ~/ira2_ws/install/setup.bash && "
            "ros2 run haptic_teleop haptic_control_dual"
        ],
        "color_on": "#f59e0b",
        "color_off": "#78350f",
    },
}

# ─── App ─────────────────────────────────────────────────────────────────────

class SphereLauncher(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("SPHERE Launcher")
        self.configure(bg="#0f172a")
        self.resizable(True, True)

        self.processes = {}   # key -> subprocess.Popen
        self.buttons   = {}   # key -> tk.Button
        self.log_areas = {}   # key -> scrolledtext.ScrolledText

        self._build_ui()
        self.protocol("WM_DELETE_WINDOW", self._on_close)

    # ── UI ───────────────────────────────────────────────────────────────────

    def _build_ui(self):
        # Titre
        header = tk.Label(
            self, text="SPHERE  LAUNCHER",
            bg="#0f172a", fg="#94a3b8",
            font=("Courier New", 11, "bold"),
            padx=16, pady=10
        )
        header.pack(fill="x")

        separator = tk.Frame(self, bg="#1e293b", height=1)
        separator.pack(fill="x")

        # Un bloc par commande
        for key, cfg in COMMANDS.items():
            frame = tk.Frame(self, bg="#0f172a", pady=6, padx=12)
            #frame.pack(fill="x")
            frame.pack(fill="both", expand=True)

            # Ligne bouton + status
            top = tk.Frame(frame, bg="#0f172a")
            top.pack(fill="x")

            btn = tk.Button(
                top,
                text=f"  {cfg['label']}  ▶",
                bg=cfg["color_off"], fg="white",
                activebackground=cfg["color_on"],
                activeforeground="white",
                font=("Courier New", 10, "bold"),
                relief="flat", bd=0,
                cursor="hand2",
                padx=14, pady=8,
                command=lambda k=key: self._toggle(k)
            )
            btn.pack(side="left")
            self.buttons[key] = btn

            status = tk.Label(
                top, text="● STOPPED",
                bg="#0f172a", fg="#475569",
                font=("Courier New", 9)
            )
            status.pack(side="left", padx=10)
            # on stocke le label de status dans le dict buttons pour y accéder
            self.buttons[key + "_status"] = status

            # Zone log (repliée au départ, petite hauteur)
            log = scrolledtext.ScrolledText(
                frame,
                height=5, width=80,
                bg="#020617", fg="#94a3b8",
                font=("Courier New", 8),
                insertbackground="white",
                state="disabled",
                relief="flat",
            )
            #log.pack(fill="x", pady=(4, 0))
            log.pack(fill="both", expand=True, pady=(4, 0))
            self.log_areas[key] = log

            sep = tk.Frame(self, bg="#1e293b", height=1)
            sep.pack(fill="x")

        # Bouton "Tout lancer" + "Tout stopper"
        footer = tk.Frame(self, bg="#0f172a", pady=10, padx=12)
        footer.pack(fill="x")

        tk.Button(
            footer, text="⊙  Tare capteur",
            bg="#0f4c75", fg="white",
            activebackground="#1b6ca8",
            font=("Courier New", 10, "bold"),
            relief="flat", cursor="hand2",
            padx=14, pady=8,
            command=self._tare
        ).pack(side="left", padx=(0, 8))

        tk.Button(
            footer, text="▶▶  Tout lancer",
            bg="#4f46e5", fg="white",
            activebackground="#6366f1",
            font=("Courier New", 10, "bold"),
            relief="flat", cursor="hand2",
            padx=14, pady=8,
            command=self._start_all
        ).pack(side="left", padx=(0, 8))

        tk.Button(
            footer, text="■  Tout stopper",
            bg="#7f1d1d", fg="white",
            activebackground="#dc2626",
            font=("Courier New", 10, "bold"),
            relief="flat", cursor="hand2",
            padx=14, pady=8,
            command=self._stop_all
        ).pack(side="left")

        self._tare_label = tk.Label(
            footer, text="",
            bg="#0f172a", fg="#22c55e",
            font=("Courier New", 9)
        )
        self._tare_label.pack(side="left", padx=10)

    # ── Logique ──────────────────────────────────────────────────────────────

    def _toggle(self, key):
        if key in self.processes and self.processes[key].poll() is None:
            self._stop(key)
        else:
            self._start(key)

    def _start(self, key):
        if key in self.processes and self.processes[key].poll() is None:
            return  # déjà en cours

        cfg = COMMANDS[key]
        self._log(key, f">>> Lancement : {cfg['label']}\n")

        try:
            proc = subprocess.Popen(
                cfg["cmd"],
                stdout=subprocess.PIPE,
                stderr=subprocess.STDOUT,
                text=True,
                bufsize=1,
                preexec_fn=os.setsid,  # groupe de process pour kill propre
            )
        except Exception as e:
            self._log(key, f"[ERREUR] {e}\n")
            return

        self.processes[key] = proc
        self._set_running(key, True)

        # Thread de lecture stdout
        t = threading.Thread(target=self._read_output, args=(key, proc), daemon=True)
        t.start()

    def _stop(self, key):
        proc = self.processes.get(key)
        if proc and proc.poll() is None:
            try:
                os.killpg(os.getpgid(proc.pid), signal.SIGTERM)
            except Exception:
                proc.terminate()
            self._log(key, ">>> Processus arrêté.\n")
        self._set_running(key, False)

    def _start_all(self):
        for key in COMMANDS:
            if key in ("haptic", "haptic_dual", "haptic_dual_full"):
                continue  # on lance le bon node haptique à la main
            self._start(key)
        # for key in COMMANDS:
        #     self._start(key)

    def _stop_all(self):
        for key in COMMANDS:
            self._stop(key)

    def _read_output(self, key, proc):
        for line in proc.stdout:
            self._log(key, line)
        # Processus terminé
        self.after(0, lambda: self._set_running(key, False))

    def _set_running(self, key, running: bool):
        cfg = COMMANDS[key]
        btn = self.buttons[key]
        status = self.buttons[key + "_status"]
        if running:
            btn.config(
                text=f"  {cfg['label']}  ■",
                bg=cfg["color_on"]
            )
            status.config(text="● RUNNING", fg=cfg["color_on"])
        else:
            btn.config(
                text=f"  {cfg['label']}  ▶",
                bg=cfg["color_off"]
            )
            status.config(text="● STOPPED", fg="#475569")

    def _log(self, key, text: str):
        def _write():
            area = self.log_areas[key]
            area.config(state="normal")
            area.insert("end", text)
            area.see("end")
            area.config(state="disabled")
        self.after(0, _write)

    def _tare(self):
        def _run():
            result = subprocess.run(
                ["bash", "-c",
                 "source /opt/ros/jazzy/setup.bash && "
                 "source ~/ira2_ws/install/setup.bash && "
                 "ros2 service call /tare_sensor std_srvs/srv/Trigger '{}'"],
                capture_output=True, text=True
            )
            if "success=True" in result.stdout:
                self._tare_status("✓ Tare OK", "#22c55e")
            else:
                self._tare_status("✗ Tare échouée", "#ef4444")

        self._tare_status("⏳ Tare...", "#94a3b8")
        threading.Thread(target=_run, daemon=True).start()

    def _tare_status(self, text, color):
        self.after(0, lambda: self._tare_label.config(text=text, fg=color))

    def _on_close(self):
        self._stop_all()
        self.destroy()


# ─── Main ─────────────────────────────────────────────────────────────────────

if __name__ == "__main__":
    app = SphereLauncher()
    app.mainloop()