#!/usr/bin/env python3
"""
IHM de lancement rapide des noeuds ROS2
Lancer avec : python3 teleop_ihm.py
"""

import tkinter as tk
from tkinter import scrolledtext
import subprocess
import threading
import os
import signal

import rclpy
from rclpy.node import Node
from std_msgs.msg import Float64, Bool # Ajouté le 16/07

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
        "color_on": "#3b82f6",
        "color_off": "#e2e8f0",
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
        "color_off": "#e2e8f0",
    },
    "haptic_dual_full": {
        "label": "③ Haptic Teleoperation Dual-user",
        "cmd": [
            "bash", "-c",
            "source /opt/ros/jazzy/setup.bash && "
            "source ~/ira2_ws/install/setup.bash && "
            "ros2 run haptic_teleop haptic_control_dual"
        ],
        "color_on": "#3b82f6",
        "color_off": "#e2e8f0",
    },
}

# Ajouté le 16/07 ###################################################
class AlphaNode(Node):
    def __init__(self, on_scaling_debug=None):
        super().__init__('teleop_ihm_alpha_node')
        self.alpha_pub = self.create_publisher(Float64, '/alpha', 10)

        # Ajouté le 16/07 : scaling manuel (enable + valeur)
        self.scaling_enable_pub = self.create_publisher(Bool, '/scaling_manual_enable', 10)
        self.scaling_manual_pub = self.create_publisher(Float64, '/scaling_manual', 10)

        # Ajouté le 16/07 : écoute du scaling reellement applique par le C++
        self._on_scaling_debug = on_scaling_debug
        self.scaling_debug_sub = self.create_subscription(
            Float64, '/scaling_debug', self._scaling_debug_cb, 10)

    def publish_alpha(self, value: float):
        msg = Float64()
        msg.data = value
        self.alpha_pub.publish(msg)

    # Ajouté le 16/07
    def publish_scaling_enable(self, enabled: bool):
        msg = Bool()
        msg.data = enabled
        self.scaling_enable_pub.publish(msg)

    def publish_scaling_manual(self, value: float):
        msg = Float64()
        msg.data = value
        self.scaling_manual_pub.publish(msg)

    def _scaling_debug_cb(self, msg):
        if self._on_scaling_debug is not None:
            self._on_scaling_debug(msg.data)
######################################################################

# ─── App ─────────────────────────────────────────────────────────────────────

class SphereLauncher(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("IHM Téléopération")
        self.configure(bg="#f1f5f9")
        self.resizable(True, True)
        self.minsize(850, 400)

        self.processes = {}   # key -> subprocess.Popen
        self.buttons   = {}   # key -> tk.Button
        self.log_areas = {}   # key -> scrolledtext.ScrolledText

        self._build_ui()

        rclpy.init()
        self.alpha_node = AlphaNode(on_scaling_debug=self._on_scaling_debug) # Ajouté le 16/07
        self.ros_thread = threading.Thread(target=rclpy.spin, args=(self.alpha_node,), daemon=True)
        self.ros_thread.start()

        # Publier la valeur initiale du slider pour synchroniser le C++ dès le lancement
        self.alpha_node.publish_alpha(self.alpha_var.get())

        self.protocol("WM_DELETE_WINDOW", self._on_close)

    # ── UI ───────────────────────────────────────────────────────────────────

    def _build_ui(self):

        separator = tk.Frame(self, bg="#cbd5e1", height=1)
        separator.pack(fill="x")

        # Un bloc par commande
        for key, cfg in COMMANDS.items():
            frame = tk.Frame(self, bg="#f1f5f9", pady=6, padx=12)
            #frame.pack(fill="x")
            frame.pack(fill="both", expand=True)

            # Ligne bouton + status
            top = tk.Frame(frame, bg="#f1f5f9")
            top.pack(fill="x")

            btn = tk.Button(
                top,
                text=f"  {cfg['label']}  ▶",
                padx=14, pady=8,
                command=lambda k=key: self._toggle(k)
            )
            btn.pack(side="left")
            self.buttons[key] = btn

            status = tk.Label(
                top, text="ARRÊTÉ",
                bg="#f1f5f9", fg="#94a3b8",
            )
            status.pack(side="left", padx=10)
            # on stocke le label de status dans le dict buttons pour y accéder
            self.buttons[key + "_status"] = status

            # Zone log (repliée au départ, petite hauteur)
            log = scrolledtext.ScrolledText(
                frame,
                height=5, width=80,
                bg="#ffffff", fg="#334155",
                insertbackground="white",
                state="disabled",
                relief="flat",
            )
            #log.pack(fill="x", pady=(4, 0))
            log.pack(fill="both", expand=True, pady=(4, 0))
            self.log_areas[key] = log

            sep = tk.Frame(self, bg="#cbd5e1", height=1)
            sep.pack(fill="x")


        
        # Slider Autorité de l'expert
        alpha_frame = tk.Frame(self, bg="#f1f5f9", padx=12)
        alpha_frame.pack(fill="x", pady=(10, 0))

        tk.Label(
            alpha_frame, text="Autorité de l'expert : ",
            bg="#f1f5f9",
        ).pack(side="left", padx=(0, 10))

        self.alpha_var = tk.DoubleVar(value=0.8)

        self.alpha_slider = tk.Scale(
            alpha_frame,
            from_=0.0, to_=1.0, resolution=0.01,
            orient="horizontal", length=250,
            bg="#f1f5f9", fg="#334155",
            highlightthickness=0, troughcolor="grey85",
            variable=self.alpha_var,
            command=self._on_alpha_change,
            showvalue=False
        )
        self.alpha_slider.pack(side="left")

        self.alpha_expert_label = tk.Label(
            alpha_frame, text="Expert: 80%",
            bg="#f1f5f9",
            width=11, anchor="w"
        )
        self.alpha_expert_label.pack(side="left", padx=(10, 0))

        tk.Label(
            alpha_frame, text="|",
            bg="#f1f5f9",
        ).pack(side="left", padx=(5, 8))

        self.alpha_learner_label = tk.Label(
            alpha_frame, text="Apprenant: 20%",
            bg="#f1f5f9",
            anchor="w"
        )
        self.alpha_learner_label.pack(side="left")

        #### Scaling manuel (Ajouté le 16/07) ################################
        scaling_frame = tk.Frame(self, bg="#f1f5f9", padx=12, height=50)
        scaling_frame.pack(fill="x", pady=(10, 0))
        scaling_frame.pack_propagate(False)

        #ajouté le 28/08
        tk.Label(
            scaling_frame, text="Ratio de mouvement : ",
            bg="#f1f5f9",
        ).pack(side="left", padx=(0, 10))

        self.manual_scaling_var = tk.BooleanVar(value=False)
        tk.Radiobutton(
            scaling_frame, text="Automatique", variable=self.manual_scaling_var,
            value=False, command=self._on_scaling_enable_change,
            bg="#f1f5f9", selectcolor="grey85",
            activebackground="#f1f5f9", highlightthickness=0,
        ).pack(side="left", padx=(0, 5))

        tk.Radiobutton(
            scaling_frame, text="Manuel", variable=self.manual_scaling_var,
            value=True, command=self._on_scaling_enable_change,
            bg="#f1f5f9", selectcolor="grey85",
            activebackground="#f1f5f9", highlightthickness=0,
        ).pack(side="left", padx=(0, 10))
        #####################################

        self.scaling_var = tk.DoubleVar(value=0.1)
        self.scaling_slider = tk.Scale(
            scaling_frame,
            from_=0.1, to_=1.0, resolution=0.01,
            orient="horizontal", length=200,
            bg="#f1f5f9", fg="#334155",
            highlightthickness=0, troughcolor="grey85",
            variable=self.scaling_var,
            command=self._on_scaling_manual_change,
            showvalue=False,
            state="disabled",   # actif seulement quand la case est cochée
        )

        self.scaling_manual_var = tk.StringVar(value="0.10")
        self.scaling_manual_label = tk.Entry(
            scaling_frame, textvariable=self.scaling_manual_var,
            width=6, justify="center",
            state="readonly", cursor="arrow"
        )

        scaling_live_frame = tk.Frame(self, bg="#f1f5f9", padx=12)
        scaling_live_frame.pack(fill="x", pady=(10, 10))

        tk.Label(
            scaling_live_frame, text="Ratio actuellement appliqué au robot :",
            bg="#f1f5f9",
        ).pack(side="left", padx=(0, 8))

        self.scaling_live_var = tk.StringVar(value="--")
        self.scaling_live_label = tk.Entry(
            scaling_live_frame, textvariable=self.scaling_live_var,
            width=6, justify="center",
            state="readonly", cursor="arrow"
        )
        self.scaling_live_label.pack(side="left", padx=(0, 8))

        self.scaling_live_detail = tk.Label(
            scaling_live_frame, text="(1cm de main = . . . cm de robot)",
            bg="#f1f5f9",
        )
        self.scaling_live_detail.pack(side="left")
        ###########################################################

        # Bouton "Tout lancer" + "STOP"
        footer = tk.Frame(self, bg="#f1f5f9", pady=10, padx=12)
        footer.pack(fill="x")

        tk.Button(
            footer, text="Tare capteur",
            padx=14, pady=8,
            command=self._tare
        ).pack(side="left", padx=(0, 8))

        tk.Button(
            footer, text="▶▶  Tout lancer",
            padx=14, pady=8,
            command=self._start_all
        ).pack(side="left", padx=(0, 8))

        tk.Button(
            footer, text="■  STOP",
            bg="#dc2626", fg="white",
            font=("TkDefaultFont", 9, "bold"),
            padx=14, pady=8,
            command=self._stop_all
        ).pack(side="left")

        self._tare_label = tk.Label(
            footer, text="",
            bg="#f1f5f9", fg="#22c55e",
        )
        self._tare_label.pack(side="left", padx=10)

    # ── Logique ──────────────────────────────────────────────────────────────

    def _toggle(self, key):
        if key in self.processes and self.processes[key].poll() is None:
            self._stop(key)
        else:
            self._start(key)

    def _on_alpha_change(self, value):
        val = float(value)
        expert_pct = val * 100
        learner_pct = (1.0 - val) * 100
        self.alpha_expert_label.config(text=f"Expert: {expert_pct:.0f}%")
        self.alpha_learner_label.config(text=f"Apprenant: {learner_pct:.0f}%")
        self.alpha_node.publish_alpha(val)

    ### Scaling manuel (Ajouté le 16/07) ################################################
    ## Modifié le 28/08
    def _on_scaling_enable_change(self):
        enabled = self.manual_scaling_var.get()
        if enabled:
            self.scaling_slider.config(state="normal")
            self.scaling_slider.pack(side="left")
            self.scaling_manual_label.pack(side="left", padx=10)
        else:
            self.scaling_slider.config(state="disabled")
            self.scaling_slider.pack_forget()
            self.scaling_manual_label.pack_forget()
            self.scaling_live_var.set("--")
            self.scaling_live_detail.config(text="(1cm de main = . . . cm de robot)")
        self.alpha_node.publish_scaling_enable(enabled)
        if enabled:
            self.alpha_node.publish_scaling_manual(self.scaling_var.get())

    def _on_scaling_manual_change(self, value):
        val = float(value)
        self.scaling_manual_var.set(f"{val:.2f}")
        if self.manual_scaling_var.get():
            self.alpha_node.publish_scaling_manual(val)
            mm = val * 10.0
            self.scaling_live_var.set(f"{val:.2f}")
            self.scaling_live_detail.config(
                text=f"(1cm de main = {mm/10:.2f}cm de robot)"
            )

    def _on_scaling_debug(self, value):
        # appelé depuis le thread ROS -> repasser dans le thread Tk
        mm = value * 10.0  # 1 cm main = (scaling*10) mm robot
        self.after(0, lambda: self.scaling_live_var.set(f"{value:.2f}"))
        self.after(0, lambda: self.scaling_live_detail.config(
            text=f"(1cm de main = {mm/10:.2f}cm de robot)"))
    #####################################################################################

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
            self._start(key)

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
            btn.config(text=f"  {cfg['label']}  ■")
            status.config(text="ACTIF", fg="#22c55e", font=("TkDefaultFont", 9, "bold"))
        else:
            btn.config(text=f"  {cfg['label']}  ▶")
            status.config(text="ARRÊTÉ", fg="#94a3b8")

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
        self.alpha_node.destroy_node()
        rclpy.shutdown()
        self.destroy()


# ─── Main ─────────────────────────────────────────────────────────────────────

if __name__ == "__main__":
    app = SphereLauncher()
    app.mainloop()