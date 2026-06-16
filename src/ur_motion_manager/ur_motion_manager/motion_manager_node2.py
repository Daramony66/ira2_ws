# Ajouté le 16/04 à 10h15 , Modifié à 11h50
# SCRIPT PROPRE

import rclpy
from rclpy.node import Node
from masters_msgs.srv import AppControlService, ContactPointService, SystemStateService # Ajouté le 16/04 à 10h30
from masters_msgs.msg import StartMove # Ajouté le 21/04 à 16h00

from std_msgs.msg import String # Ajouté le 16/04 à 12h35

import rtde_control
import rtde_receive
from scipy.spatial.transform import Rotation as R
import math
import threading
import time # Déplacé le 15/04

import subprocess # Ajouté le 17/04 à 17h00

import socket, struct # Ajouté le 19/05

from rcl_interfaces.msg import SetParametersResult # Ajouté le 16/04 à 17h00 -- pour les paramètres dynamiques

from std_srvs.srv import Trigger  # service simple sans paramètre # Ajouté le 21/04

import rclpy.parameter

import csv, os

# Ajouté le 17/04 à 16h30
def publish_status(status: str):
    cmd = f'ros2 topic pub --once /masters/status std_msgs/msg/String "{{data: \\"{status}\\"}}"'
    threading.Thread(
        target=lambda: subprocess.run(cmd, shell=True, capture_output=True),
        daemon=True
    ).start()

class TestUnityP1(Node):
    def __init__(self):
        super().__init__('test_unity_p1')

        self.rc = rtde_control.RTDEControlInterface("192.168.1.101")
        self.rr = rtde_receive.RTDEReceiveInterface("192.168.1.101")

        # Position initiale
        self.init_pose = [
            # math.radians(-45),
            # math.radians(-135),
            # math.radians(-90),
            # math.radians(90),
            # math.radians(-180),
            # math.radians(-90),
            # math.radians(180),

            # POSITION TEST

            # math.radians(-135),
            # math.radians(-145),
            # math.radians(90),
            # math.radians(-90),
            # math.radians(-90),
            # math.radians(180),

            # POSITION INIT TEST 12/05 (pose épaule droite)

            # math.radians(-135),
            # math.radians(-135),
            # math.radians(105),
            # math.radians(-150),
            # math.radians(-90),
            # math.radians(180),

            # POSITION TEST 20/05 POUR VITESSE
            # math.radians(-315),
            # math.radians(-90),
            # math.radians(120),
            # math.radians(-210),
            # math.radians(-90),
            # math.radians(180),

            # POSITION INIT TEST 13/05 (pose épaule gauche)
            # math.radians(45),
            # math.radians(-45),
            # math.radians(-105),
            # math.radians(-30),
            # math.radians(90),
            # math.radians(180),



            # POSE 26/05 - symétrie gauche mais J4 vers le haut --- POSE SAUVEGARDEE
            # math.radians(0),
            # math.radians(-135),
            # math.radians(-135),
            # math.radians(90),
            # math.radians(90),
            # math.radians(0),

            # POSE 28/05 - symétrie gauche mais J4 vers le bas et NON resserré (ex FINALE)
            # math.radians(0),
            # math.radians(-115),
            # math.radians(-135),
            # math.radians(-110),
            # math.radians(270),
            # math.radians(0),

            # POSE 05/06 - symétrie gauche mais J4 vers le bas et resserré (ex FINALE)
            # math.radians(0),
            # math.radians(-110),
            # math.radians(-148),
            # math.radians(-102),
            # math.radians(270),
            # math.radians(0),

            # POSE 05/06 - symétrie gauche mais J4 vers le haut pour éviter de cogner mais pb de plan de sécurité
            # math.radians(0),
            # math.radians(-115),
            # math.radians(-143),
            # math.radians(78),
            # math.radians(90),
            # math.radians(0),

            # POSE 05/06 - robot symétrie à droite pour éviter de cogner
            # math.radians(180),
            # math.radians(-70),
            # math.radians(150),
            # math.radians(-80),
            # math.radians(90),
            # math.radians(0),

            # POSE 09/06 - POSE TEST en partant de symétrie droite mais décaler tout à gauche
            # math.radians(120),
            # math.radians(-65),
            # math.radians(100),
            # math.radians(-35),
            # math.radians(30),
            # math.radians(0),

            # POSE 10/06 - POSE TEST en partant de symétrie droite mais décaler tout à gauche (mieux)
            math.radians(102.37),
            math.radians(-78.69),
            math.radians(119.85),
            math.radians(-41.10),
            math.radians(12.36),
            math.radians(0),

        ]

        self.get_logger().info("Déplacement vers position initiale...") #Ajouté le 15/04

        # Aller en position initiale + calculer z_axis_in_base et orientation
        # self.rc.moveJ(self.init_pose, 0.1, 0.1)
        self.rc.moveJ(self.init_pose, 0.5, 0.5) # vitesse plus élevée
        
        self.get_logger().info("Position initiale atteinte.") #Ajouté le 15/04

        #Récupérer les coordonnées(POSITION + ROTATION) du vecteur Z_TCP dans le repère base
        tcp = self.rr.getActualTCPPose()
        self.tcp_z_init = tcp[2]
        self.orientation = [tcp[3], tcp[4], tcp[5]]
        rot = R.from_rotvec(tcp[3:6])
        self.z_axis_in_base = rot.as_matrix()[:, 2]
        self.tcp_init_pose = list(tcp)  # ← ICI

        self.error_event = threading.Event()

        #Ajouté le 16/04 à 12h35
        self.abort_active = False

        # Ajouté le 26/05 — reprise du dernier numéro d'essai depuis timing_data.csv
        timing_path = os.path.expanduser('~/ira2_ws/timing_data.csv')
        if os.path.exists(timing_path):
            with open(timing_path, 'r') as f:
                rows = list(csv.reader(f))
                if len(rows) > 1:
                    self._essai_count = int(rows[-1][0])
                else:
                    self._essai_count = 0
        else:
            self._essai_count = 0

        csv_path = os.path.expanduser('~/ira2_ws/vitesse_data.csv')
        if os.path.exists(csv_path):
            os.remove(csv_path)

        #Ajouté je 16/04 à 16h45
        self.declare_parameter('force_target', 7.5)
        self.declare_parameter('force_wrench', 120.0)
        self.declare_parameter('force_max', 100.0)
        self.declare_parameter('scenario_mode', 3)  # Push par défaut
        self.declare_parameter('timeout', 30.0)
        self.declare_parameter('offset', 0.05)
        self.declare_parameter('xy_norm_min', 0.230)
        self.declare_parameter('settle_time', 1.0)
        self.declare_parameter('bias_samples', 50)
        self.declare_parameter('bias_std_threshold', 0.5)
        self.declare_parameter('hold_time', 0.2) # Ajouté le 17/04 à 11h40

        self.force_target = self.get_parameter('force_target').value
        self.force_wrench = self.get_parameter('force_wrench').value
        self.force_max = self.get_parameter('force_max').value
        self.scenario_mode = int(self.get_parameter('scenario_mode').value)
        self.timeout = self.get_parameter('timeout').value
        self.offset = self.get_parameter('offset').value
        self.xy_norm_min = self.get_parameter('xy_norm_min').value
        self.settle_time = self.get_parameter('settle_time').value
        self.bias_samples = int(self.get_parameter('bias_samples').value)
        self.bias_std_th = self.get_parameter('bias_std_threshold').value
        self.hold_time = self.get_parameter('hold_time').value # Ajouté le 17/04 à 11h40

        self.add_on_set_parameters_callback(self.cb_parameters) # Ajouté le 16/04 à 17h00

        self.create_subscription(String, '/safety_abort', self.cb_abort, 10) #Ajouté le 16/04 à 12h35
        #######################

        self.status_pub = self.create_publisher(String, '/masters/status', 10) # Ajouté le 17/04 à 13h10

        self.start_move_event = threading.Event()
        self._moving = threading.Lock()  # Ajouté le 21/04 — verrou anti-doublons

        self.create_subscription(StartMove, 'start_move', self.cb_start_move, 10) # Modifé le 21/04 à 16h00 — changement de type de message

        self.get_logger().info(f"Position initiale TCP : x:{tcp[0]*1000:.2f}mm  y:{tcp[1]*1000:.2f}mm  z:{tcp[2]*1000:.2f}mm")  # Afficher pose TCP dans repère base

        self.get_logger().info(f"Z axis in base : x:{self.z_axis_in_base[0]:.4f}  y:{self.z_axis_in_base[1]:.4f}  z:{self.z_axis_in_base[2]:.4f}") # Afficher coords vecteur Z_TCP dans repère base
        
        # Ajouté le 21/04 — clients de service Unity
        self.app_control_client = self.create_client(AppControlService, 'app_control')
        self.contact_point_client = self.create_client(ContactPointService, 'cp_position')
        self.state_client = self.create_client(SystemStateService, 'system_state')

        self.create_service(Trigger, 'start_session', self.cb_start_session) # Ajouté le 21/04 — service pour démarrer la session depuis IHM

        self.create_service(SystemStateService, 'set_scenario', self.cb_set_scenario) # Ajouté le 22/04 à 10h00 — service pour changer de scénario depuis IHM
        
        self.get_logger().info("En attente de P1 depuis Unity...")

        # Ajouté le 21/04 — test : appuyer Entrée pour démarrer la session
        # threading.Thread(target=self._wait_input, daemon=True).start()

        self.get_logger().info("Nœud prêt — statut ready publié.")
        time.sleep(2.0)
        for _ in range(5):
            msg = String()
            msg.data = "restarted"
            self.status_pub.publish(msg)
            time.sleep(0.3)

    # def cb_p1(self, msg):
    #     P1 = [msg.x, msg.y, msg.z]
    #     self.get_logger().info(f"P1 reçu : x={P1[0]:.4f}  y={P1[1]:.4f}  z={P1[2]:.4f}")
    #     t = threading.Thread(target=self.move_to_p1, args=(P1,))
    #     t.start()

    # Ajouté le 21/04 — demande la position à Unity via service
    def request_contact_point(self):
        if not self.contact_point_client.service_is_ready():
            self.get_logger().warn("Service cp_position pas disponible — Unity connecté ?")
            return
        req = ContactPointService.Request()
        req.command = 0
        future = self.contact_point_client.call_async(req)
        future.add_done_callback(self.cb_contact_point)

    def cb_contact_point(self, future):
        response = future.result()
        if not response.success:
            self.get_logger().error("cp_position a retourné success=False")
            return
        P1 = [response.position.x, response.position.y, response.position.z]
        self.get_logger().info(f"P1 reçu : x={P1[0]:.4f}  y={P1[1]:.4f}  z={P1[2]:.4f}")
        
        if not self._moving.acquire(blocking=False):
            self.get_logger().warn("Mouvement déjà en cours — P1 ignoré.")
            return
        t = threading.Thread(target=self._move_wrapper, args=(P1,))
        t.start()

    def _move_wrapper(self, P1):
        try:
            self.move_to_p1(P1)
        finally:
            self._moving.release()
            # if not self.error_event.is_set():
            #     self.node_ready_event.set()

    # Ajouté le 21/04 — démarre une session : récupère P1 puis lance Unity
    def start_session(self):
        self.abort_active = False  # reset abort
        self.error_event.clear()   # reset error
        # Ajouté le 22/04 à 10h00 — mode de scénario dynamique selon paramètre ############
        # if self.scenario_mode == 2:
        #     self.change_state(2)  # Punch
        # elif self.scenario_mode == 3:
        #     self.change_state(3)  # Push
        ###################################################################################
        if not self.contact_point_client.service_is_ready():
            self.get_logger().warn("Service cp_position pas disponible — Unity connecté ?")
            return
        req = ContactPointService.Request()
        req.command = 0
        self.get_logger().info("Service cp_position appelé.")
        future = self.contact_point_client.call_async(req)
        future.add_done_callback(self.cb_contact_point)

    # Ajouté le 21/04 — callback pour service de démarrage depuis IHM
    def cb_start_session(self, request, response):
        self.start_session()
        response.success = True
        response.message = "Session démarrée"
        return response
    
    def cb_set_scenario(self, request, response):
        self.scenario_mode = request.command
        self.set_parameters([rclpy.parameter.Parameter('scenario_mode', rclpy.Parameter.Type.INTEGER, request.command)])
        self.change_state(request.command)
        response.success = True
        return response

    def change_state(self, state_id):
        self.get_logger().info(f"Service system_state appelé — command={state_id}")
        if not self.state_client.service_is_ready():
            self.get_logger().warn("Service system_state pas disponible.")
            return
        req = SystemStateService.Request()
        req.command = state_id
        future = self.state_client.call_async(req)
        future.add_done_callback(lambda f: self.get_logger().info(
            f"system_state réponse : success={f.result().success}"))

    # Ajouté le 21/04 — attend Entrée puis démarre la session
    # def _wait_input(self):
    #     while True:
    #         input("Appuyez sur Entrée pour démarrer la session...")
    #         try:
    #             self.start_session()
    #         except Exception as e:
    #             print(f"[_wait_input] Erreur : {e}")

    #Ajouté le 16/04 à 12h35
    def cb_abort(self, msg):
        self.abort_active = True
        self.get_logger().error(f"SAFETY ABORT reçu : {msg.data}")

    def cb_start_move(self, msg):
        if msg.start:
            self.get_logger().info("Signal /start_move reçu — lancement poussée.")
            self.start_move_event.set()

    #Ajouté le 15/04
    def destroy_node(self):
        try:
            self.rc.servoStop()
            self.rc.forceModeStop()
            self.rc.stopScript()
            self.rc.disconnect()
            self.rr.disconnect()
        except:
            pass
        super().destroy_node()

    # Ajouté le 19/05 — lecture robotDexterity via primary client port 30001
    def _get_robot_dexterity(self):
        for attempt in range(3):
            try:
                s = socket.socket()
                s.settimeout(5.0)
                s.connect(('192.168.1.101', 30001))
                # time.sleep(0.5)
                # data = s.recv(4096)
                # self.get_logger().warn(f"[DEXTERITY] data reçue : {len(data)} bytes, premier pkg_type={struct.unpack_from('B', data, 4)[0] if len(data)>4 else 'vide'}")
                # s.close()
                data = b''
                deadline = time.time() + 5.0
                while len(data) < 4096 and time.time() < deadline:
                    chunk = s.recv(4096)
                    if not chunk:
                        break
                    data += chunk
                # self.get_logger().warn(f"[DEXTERITY] data accumulée : {len(data)} bytes")
                # types_vus = set()
                # ii = 0
                # while ii < len(data) - 5:
                #     ps = struct.unpack_from('>I', data, ii)[0]
                #     pt = struct.unpack_from('B', data, ii+4)[0]
                #     types_vus.add(pt)
                #     ii += ps if ps > 0 else 1
                # self.get_logger().warn(f"[DEXTERITY] pkg_types vus : {types_vus}")
                s.close()
                i = 0
                while i < len(data) - 5:
                    pkg_size = struct.unpack_from('>I', data, i)[0]
                    pkg_type = struct.unpack_from('B', data, i+4)[0]
                    if pkg_type in (16, 20):
                        j = i + 5
                        while j < i + pkg_size:
                            sub_size = struct.unpack_from('>I', data, j)[0]
                            sub_type = struct.unpack_from('B', data, j+4)[0]
                            if sub_type == 7:
                                dexterity = struct.unpack_from('>d', data, j+5+48)[0]
                                return dexterity
                            j += sub_size if sub_size > 0 else 1
                    i += pkg_size if pkg_size > 0 else 1
            except Exception as e:
                self.get_logger().warn(f"[DEXTERITY] Tentative {attempt+1}/3 échouée : {type(e).__name__} — {e}")
                if attempt < 2:
                    time.sleep(0.3)
        return None

    def move_to_p1(self, P1):
        # Aller directement en P1 pour vérifier calibration Unity <-> robot réel #JUSTE POUR VERIFIER
        # self.rc.moveL([P1[0], P1[1], P1[2],
        #                self.orientation[0], self.orientation[1], self.orientation[2]],
        #                0.05, 0.05)
        # tcp = self.rr.getActualTCPPose()
        # self.get_logger().info(f"En P1 ! TCP réel : x:{tcp[0]*1000:.2f}mm  y:{tcp[1]*1000:.2f}mm  z:{tcp[2]*1000:.2f}mm")

        self.start_move_event.clear()  # Ajouté le 20/04 — évite les signaux résiduels

        # Ajouté le 16/04 à 12h35
        if self.abort_active:

            ############################
            msg = String()
            msg.data = "aborted"
            self.status_pub.publish(msg)
            ############################

            self.get_logger().warn("Abort actif — mouvement annulé.")
            return


        # =====================================================
        # SUITE - A décommenter une fois calibration validée
        # =====================================================

        # # ETAPE pre_P1 : reculer de 10cm en Z TCP avant P1
        # offset = self.offset
        # pre_P1 = [

        # Ajouté le 22/04 à 10h00
        if self.scenario_mode == 2:    # Punch
            offset = self.offset
            wrench = [0, 0, self.force_wrench, 0, 0, 0]
        elif self.scenario_mode == 3:  # Push
            offset = self.offset
            wrench = [0, 0, self.force_wrench, 0, 0, 0]
        elif self.scenario_mode == 4:  # Touch
            offset = 0.05
            wrench = [0, 0, 10.0, 0, 0, 0]
        else:
            offset = self.offset
            wrench = [0, 0, self.force_wrench, 0, 0, 0]

        pre_P1 = [
            P1[0] - self.z_axis_in_base[0] * offset,
            P1[1] - self.z_axis_in_base[1] * offset,
            P1[2] - self.z_axis_in_base[2] * offset,
            self.orientation[0], self.orientation[1], self.orientation[2],
        ]

        # ### Ajouté le 16/04 pour les limites avec la norme ###
        # xy_norm = math.sqrt(pre_P1[0]**2 + pre_P1[1]**2)
        # self.get_logger().info(f"Norme XY pre_P1 = {xy_norm*1000:.1f}mm") # Afficher la norme

        # # testé empiriquement valeur trouvé
        # # if xy_norm < 0.2265:
        # #     self.get_logger().warn(f"pre_P1 trop proche de la base (norme XY = {xy_norm*1000:.1f}mm < 226.5mm) — renvoyer un autre point.")
        # #     return
        
        # # valeur repoussé à 230 pour plus de sûreté
        # if xy_norm < self.xy_norm_min:
        #     ############################
        #     msg = String()
        #     msg.data = "aborted_norm" # Mise à jour le 20/40 à 12h00
        #     self.status_pub.publish(msg)
        #     ############################
        #     self.get_logger().warn(f"pre_P1 trop proche de la base (norme XY = {xy_norm*1000:.1f}mm < 230mm) — renvoyer un autre point.")
        #     return

        # #################################

        # self.rc.moveL(pre_P1, 0.05, 0.05)
        # print(f"En pre_P1 !")

        # Ajouté le 28/05 — rejet des points hors plage de hauteur (±30cm)
        if pre_P1[2] < self.tcp_z_init - 0.300 or pre_P1[2] > self.tcp_z_init + 0.300:
            self.get_logger().warn(f"pre_P1 hors plage de hauteur (z={pre_P1[2]*1000:.1f}mm) — point rejeté.")
            msg = String()
            msg.data = "aborted_norm"
            self.status_pub.publish(msg)
            return

        # Ajouté le 20/05 — rejet des points derrière l'outil 1
        tcp_init = self.rr.getActualTCPPose()
        vec_to_pre_p1 = [
            pre_P1[0] - tcp_init[0],
            pre_P1[1] - tcp_init[1],
            pre_P1[2] - tcp_init[2],
        ]
        dot = (vec_to_pre_p1[0] * self.z_axis_in_base[0] +
            vec_to_pre_p1[1] * self.z_axis_in_base[1] +
            vec_to_pre_p1[2] * self.z_axis_in_base[2])
        # if dot < 0:
        #     self.get_logger().warn("pre_P1 derrière l'outil — point rejeté.")
        #     msg = String()
        #     msg.data = "aborted_norm"
        #     self.status_pub.publish(msg)
        #     return

        # Ajouté le 16/06 à 12h30
        if (pre_P1[1] - tcp_init[1]) < 0.290 and pre_P1[0] < tcp_init[0] + 0.050:
            self.get_logger().warn("pre_P1 rejeté — zone interdite.")
            msg = String()
            msg.data = "aborted_norm"
            self.status_pub.publish(msg)
            return
        
        if 0.290 <= (pre_P1[1] - tcp_init[1]) < 0.380 and pre_P1[0] < tcp_init[0] - 0.020:
            self.get_logger().warn("pre_P1 trop loin derrière en X — point rejeté.")
            msg = String()
            msg.data = "aborted_norm"
            self.status_pub.publish(msg)
            return
        
        if (pre_P1[1] - tcp_init[1]) >= 0.380 and pre_P1[0] < tcp_init[0] - 0.150:
            self.get_logger().warn("pre_P1 rejeté — trop loin derrière en X zone 3.")
            msg = String()
            msg.data = "aborted_norm"
            self.status_pub.publish(msg)
            return

        # Ajouté le 20/05 — vérification atteignabilité pre_P1
        if not self.rc.isPoseWithinSafetyLimits(pre_P1):
            self.get_logger().warn("pre_P1 hors limites de sécurité — point rejeté.")
            msg = String()
            msg.data = "aborted_norm"
            self.status_pub.publish(msg)
            return

        # Point intermédiaire zones 2 et 3 — Ajouté le 16/06
        if (pre_P1[1] - tcp_init[1]) >= 0.290:
            intermediate = [tcp_init[0], 0.1654, pre_P1[2],
                            self.orientation[0], self.orientation[1], self.orientation[2]]
            self.rc.moveL(intermediate, 0.05, 0.05)

        #Ajouté le 16/04 à 15h15#######################
        self.rc.moveL(pre_P1, 0.05, 0.05, asynchronous=True)

        while self.rc.getAsyncOperationProgress() >= 0:
            if self.abort_active:
                self.rc.stopL(0.5)
                msg = String()
                msg.data = "aborted"
                self.status_pub.publish(msg)
                self.get_logger().error("Abort reçu pendant moveL — arrêt immédiat.")
                return
            if self.rr.getRuntimeState() != 2:
                msg = String()
                msg.data = "error"
                self.status_pub.publish(msg)
                self.error_event.set()
                return
            time.sleep(0.02)
        print(f"En pre_P1 !")

        #### Ajouté le 09/06 ###########################################
        # Attente de stabilisation avant de lire les forces pour le bias learning, sinon on peut avoir des pics à cause du mouvement

        time.sleep(0.02)

        # Ajouté le 16/04 à 12h35
        self.rc.zeroFtSensor()
        time.sleep(self.settle_time)

        # Bias learning
        bias_buf = []
        while len(bias_buf) < self.bias_samples:
            force = self.rr.getActualTCPForce()
            mag = (force[0]**2 + force[1]**2 + force[2]**2)**0.5
            bias_buf.append(mag)
            time.sleep(0.01)

        bias_mean = sum(bias_buf) / len(bias_buf)
        bias_std = (sum((x - bias_mean)**2 for x in bias_buf) / len(bias_buf))**0.5
        self.get_logger().info(f"Bias appris : {bias_mean:.3f}N (std={bias_std:.3f}N)")

        ###############################################

        # Ajouté le 19/05 — vérification dextérité en pre_P1
        dexterity = self._get_robot_dexterity()
        if dexterity is not None:
            self.get_logger().info(f"[DEXTERITY] {dexterity:.8f}")
            if dexterity < 0.00002:
                self.get_logger().warn(f"Singularité détectée (dextérité={dexterity:.8f}) — retour position initiale.")
                self.rc.moveJ(self.init_pose, 0.5, 0.5)
                msg = String()
                msg.data = "aborted_singularity"
                self.status_pub.publish(msg)
                return
        else:
            self.get_logger().warn("[DEXTERITY] Valeur non disponible — on continue.")

        # Ajouté le 22/05
        t_play_unity = time.time()

        # Ajouté le 26/05
        t_contact = None
        t_end_push = None

        # Ajouté le 19/05 — app_control play uniquement si dextérité ok
        if self.app_control_client.service_is_ready():
            req = AppControlService.Request()
            req.command = 0  # play
            self.get_logger().info("Service app_control appelé.")
            future = self.app_control_client.call_async(req)
            future.add_done_callback(lambda f: self.get_logger().info(
                f"app_control réponse : success={f.result().success}"))

        self.start_move_event.clear()
        self.get_logger().info("En pre_P1 — en attente du signal /start_move...")

        # Publier "waiting" pour informer l'IHM
        msg = String()
        msg.data = "waiting"
        self.status_pub.publish(msg)

        # self.start_move_event.wait()  # bloque jusqu'à réception de /start_move
            
        while not self.start_move_event.wait(timeout=0.1):
            if self.abort_active:
                msg = String()
                msg.data = "aborted"
                self.status_pub.publish(msg)
                return
            if self.error_event.is_set():
                msg = String()
                msg.data = "error"
                self.status_pub.publish(msg)
                return

        if self.abort_active:
            msg = String()
            msg.data = "aborted"
            self.status_pub.publish(msg)
            return
        
        # Ajouté le 20/05 — enregistrement CSV vitesse
        t_start_move = time.time()
        self._essai_count += 1
        speed_log = []

        # ETAPE force mode : pousser en Z TCP vers P1

        tcp_current = self.rr.getActualTCPPose()
        task_frame = list(tcp_current) # repère de poussée
        selection_vector = [0, 0, 1, 0, 0, 0] # quel axe ?
        # wrench = [0, 0, self.force_wrench, 0, 0, 0] # force de poussée


        limits = [2, 2, 1.5, 1, 1, 1] # ??
        t_start_loop = time.time()
        TIMEOUT = self.timeout # temps avant mort
        #FORCE_TARGET = self.force_target # force cible

        # Ajouté le 22/04 à 10h00
        if self.scenario_mode == 4:  # Touch
            FORCE_TARGET = 1.0
        else:
            FORCE_TARGET = self.force_target

        i = 0
        
        while True:
            t_start = self.rc.initPeriod()
            self.rc.forceMode(task_frame, selection_vector, wrench, 2, limits)
            self.rc.waitPeriod(t_start)

            # Ajouté le 15/04 - détection Protective Stop
            runtime_state = self.rr.getRuntimeState()
            # if runtime_state != 2:
            #     self.error_event.set()
            #     return
            
            if runtime_state != 2:
                msg = String()
                msg.data = "error"
                self.status_pub.publish(msg)
                self.error_event.set()
                return
            
            # Ajouté le 16/04 à 15h15 
            if self.abort_active:
                self.rc.forceModeStop()
                ############################
                msg = String()
                msg.data = "aborted"
                self.status_pub.publish(msg)
                ############################                
                self.get_logger().error("Abort reçu pendant force mode — arrêt immédiat.")
                return
            
            force = self.rr.getActualTCPForce()
            force_mag = (force[0]**2 + force[1]**2 + force[2]**2)**0.5

            force_dev = force_mag - bias_mean # Ajouté le 16/04 à 12h35    
                    
            speed = self.rr.getActualTCPSpeed()
            speed_mag = (speed[0]**2 + speed[1]**2 + speed[2]**2)**0.5
            speed_log.append({
                'essai': self._essai_count,
                'temps': round(time.time() - t_start_move, 4),
                'vitesse_mm_s': round(speed_mag * 1000, 2),
                'wrench_N': int(self.force_wrench),
                'force_detectee_N': round(force_dev, 3),
            })



            # Ajouté le 16/04 à 16h45
            if force_dev > self.force_max:
                self.rc.forceModeStop()
                ############################
                msg = String()
                msg.data = "aborted"
                self.status_pub.publish(msg)
                ############################                   
                self.get_logger().error(f"Force max dépassée ({force_dev:.2f}N > {self.force_max}N) — arrêt immédiat.")
                return

            if i % 50 == 0:
                t = self.rr.getActualTCPPose()
                print(f"x:{t[0]*1000:.1f}mm  y:{t[1]*1000:.1f}mm  force:{force_dev:.2f}N") # Ajouté le 16/04 à 12h35


            # if force_dev > FORCE_TARGET: # Ajouté le 16/04 à 12h35
            #     print(f"Force cible atteinte : {force_mag:.2f}N !")
            #     break

            # if time.time() - t_start_loop > TIMEOUT:
            #     print("Timeout !")
            #     break

            # Ajouté le 17/04 à 11h00
            if force_dev >= FORCE_TARGET:
                # self.rc.forceModeStop()

                # Ajouté le 22/05
                t_contact = round(time.time() - t_start_move, 4)
                t_play_to_contact = round(time.time() - t_play_unity, 4)
                force_max = round(max((r['force_detectee_N'] for r in speed_log), default=0), 3)
                vitesse_max = round(max((r['vitesse_mm_s'] for r in speed_log), default=0), 2)

                self.get_logger().info(f"Force cible atteinte : force_dev={force_dev:.3f}N  bias_mean={bias_mean:.3f}N  force_mag={force_mag:.3f}N")
                if self.scenario_mode == 2:    # Punch
                    self.rc.forceModeStop()
                    self.get_logger().info("Mode Punch — rétraction rapide !")
                    retract_speed, retract_accel = 1.0, 2.0
                elif self.scenario_mode == 3:  # Push
                    self.get_logger().info("Mode Push — maintien...")
                    t_hold_start = time.time()
                    while time.time() - t_hold_start < self.hold_time:
                        if self.rr.getRuntimeState() != 2:
                            self.rc.forceModeStop()
                            msg = String()
                            msg.data = "error"
                            self.status_pub.publish(msg)
                            self.error_event.set()
                            return
                        speed = self.rr.getActualTCPSpeed()
                        speed_mag = (speed[0]**2 + speed[1]**2 + speed[2]**2)**0.5
                        speed_log.append({
                            'essai': self._essai_count,
                            'temps': round(time.time() - t_start_move, 4),
                            'vitesse_mm_s': round(speed_mag * 1000, 2),
                            'wrench_N': int(self.force_wrench),
                            'force_detectee_N': round(force_dev, 3), # Ajouté le 22/05
                        })
                        time.sleep(0.02)
                    
                    # Ajouté le 22/05
                    t_end_push = round(time.time() - t_start_move, 4)

                    self.rc.forceModeStop()
                    retract_speed, retract_accel = 0.2, 0.5
                elif self.scenario_mode == 4:  # Touch
                    self.rc.forceModeStop()
                    self.get_logger().info("Mode Touch — rétraction immédiate.")
                    retract_speed, retract_accel = 0.5, 1.0
                break

            if time.time() - t_start_loop > TIMEOUT:
                print("Timeout !")
                self.rc.forceModeStop()
                print("Force mode OFF")
                retract_speed, retract_accel = 0.2, 0.5
                break
            i += 1
        
        # Ajouté le 10/06 — vérification Protective Stop après contact
        if self.rr.getRuntimeState() != 2:
            msg = String()
            msg.data = "error"
            self.status_pub.publish(msg)
            self.error_event.set()
            return


        # Commenté le 17/04 à 11h00
        # self.rc.forceModeStop()
        # print("Force mode OFF")

        # ETAPE retraction : retour position initiale
        # self.rc.moveJ(self.init_pose, 0.1, 0.1)
        # print("Retour position initiale !")

        # # Commenté le 16/04 à 15h15
        # self.rc.moveL(pre_P1, 0.2, 0.5)
        # print(f"Rétracté en pre_P1 !")

        # Ajouté le 22/05
        t_retract = round(time.time() - t_start_move, 4)

        # Sauvegarde CSV vitesse
        csv_path = os.path.expanduser('~/ira2_ws/vitesse_data.csv')
        file_exists = os.path.exists(csv_path)
        with open(csv_path, 'a', newline='') as f:
            w = csv.DictWriter(f, fieldnames=['essai', 'temps', 'vitesse_mm_s', 'wrench_N', 'force_detectee_N']) # Modifié le 22/05
            if not file_exists:
                w.writeheader()
            w.writerows(speed_log)

        # Sauvegarde CSV timing — Ajouté le 22/05
        timing_path = os.path.expanduser('~/ira2_ws/timing_data.csv')
        timing_exists = os.path.exists(timing_path)
        with open(timing_path, 'a', newline='') as f:
            w = csv.writer(f)
            if not timing_exists:
                w.writerow(['essai', 'wrench_N', 'force_target_N', 'offset_m', 'hold_time_s', 'time_to_contact_s', 'time_to_end_push_s', 'time_to_retract_s', 'time_play_to_contact_s', 'force_max_N', 'vitesse_max_mm_s'])
            w.writerow([
                self._essai_count,
                int(self.force_wrench),
                self.force_target,
                self.offset,
                self.hold_time,
                t_contact,
                t_end_push,
                t_retract,
                t_play_to_contact,
                force_max,
                vitesse_max,
            ])


        # Ajouté le 16/04 à 15h15 ###############
        # self.rc.moveL(pre_P1, 0.2, 0.5, asynchronous=True) # Commenté le 17/04

        self.rc.moveL(pre_P1, retract_speed, retract_accel, asynchronous=True)


        while self.rc.getAsyncOperationProgress() >= 0:
            if self.abort_active:
                self.rc.stopL(0.5)
                ############################
                msg = String()
                msg.data = "aborted"
                self.status_pub.publish(msg)
                ############################                   
                self.get_logger().error("Abort reçu pendant rétraction — arrêt immédiat.")
                return
            if self.rr.getRuntimeState() != 2:
                msg = String()
                msg.data = "error"
                self.status_pub.publish(msg)
                self.error_event.set()
                return
            time.sleep(0.02)
        print(f"Rétracté en pre_P1 !")
        #########################################

        # self.rc.moveJ(self.init_pose, 0.5, 0.5)
        self.rc.moveL(self.tcp_init_pose, 0.2, 0.5)
        self.get_logger().info("Retour position initiale.")

        # Ajouté 17/04 à 13h10
        msg = String()
        msg.data = "ready"
        self.status_pub.publish(msg)
        self.get_logger().info("Statut : ready — en attente du prochain PLAY.")
        # self.node_ready_event.set()  # ← AJOUTER

        # self.get_logger().info("En attente de P1 depuis Unity...")

    # Ajouté le 16/04 à 17h00 -- callback pour mise à jour dynamique des paramètres depuis ROS2
    def cb_parameters(self, params):
        for p in params:
            if p.name == 'force_target':
                self.force_target = p.value
            elif p.name == 'force_wrench':
                self.force_wrench = p.value
            elif p.name == 'force_max':
                self.force_max = p.value
            elif p.name == 'scenario_mode':
                self.scenario_mode = int(p.value)
            elif p.name == 'timeout':
                self.timeout = p.value
            elif p.name == 'offset':
                self.offset = p.value
            elif p.name == 'xy_norm_min':
                self.xy_norm_min = p.value
            elif p.name == 'settle_time':
                self.settle_time = p.value
            elif p.name == 'bias_samples':
                self.bias_samples = int(p.value)
            elif p.name == 'bias_std_threshold':
                self.bias_std_th = p.value
            elif p.name == 'hold_time': # Ajouté le 17/04 à 11h40
                self.hold_time = p.value # Ajouté le 17/04 à 11h40
        return SetParametersResult(successful=True)

# def main():
#     rclpy.init()
#     node = TestUnityP1()
#     rclpy.spin(node)

# Ajouté le 15/04 à 11h06

def main():
    rclpy.init()
    node = None
    # node_ref = [None]
    # node_ready_event = threading.Event()  # ← AJOUT

    # def wait_input_global():
    #     while True:
    #         node_ready_event.wait()        # ← attend le signal
    #         node_ready_event.clear()       # ← reset pour prochain cycle
    #         time.sleep(0.1)
    #         input("Appuyez sur Entrée pour démarrer la session...")
    #         try:
    #             node_ref[0].start_session()
    #         except Exception as e:
    #             print(f"[input] Erreur : {e}")
    #         time.sleep(0.5)               # ← évite double affichage

    # threading.Thread(target=wait_input_global, daemon=True).start()

    while True:
        try:
            node = TestUnityP1()
            # node_ref[0] = node
            # node.node_ready_event = node_ready_event  # ← AJOUTER
            # node_ready_event.set()         # ← AJOUT : signal au thread
            executor = rclpy.executors.SingleThreadedExecutor()
            executor.add_node(node)
            while rclpy.ok():
                executor.spin_once(timeout_sec=0.1)
                if node.error_event.is_set():
                    raise RuntimeError("Erreur robot détectée")
        except KeyboardInterrupt:
            print(" Arrêt propre détecté...")
            if node is not None:
                try:
                    node.rc.stopScript()
                    node.rc.disconnect()
                    node.rr.disconnect()
                except:
                    pass
            break
        except Exception as e:
            print(f"[ERREUR] {e}")
            try:
                node.rc.disconnect()
            except:
                pass
            try:
                node.destroy_node()
            except:
                pass
            while True:
                time.sleep(2)
                try:
                    rr_test = rtde_receive.RTDEReceiveInterface("192.168.1.101")
                    robot_mode = rr_test.getRobotMode()
                    safety_mode = rr_test.getSafetyMode()
                    rr_test.disconnect()
                    if robot_mode == 7 and safety_mode == 1:
                        print("Robot prêt, relance dans 2s...")
                        publish_status("restarting")
                        time.sleep(2)
                        break
                    else:
                        print(f"Robot pas encore prêt (safety_mode={safety_mode}), attente...")
                except:
                    print("Connexion RTDE impossible, attente...")
        else:
            break
    try:
        rclpy.shutdown()
    except:
        pass

if __name__ == '__main__':
    main()