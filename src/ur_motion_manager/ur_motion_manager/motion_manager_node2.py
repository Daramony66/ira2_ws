# Ajouté le 16/04 à 10h15 , Modifié à 11h50
# SCRIPT PROPRE

import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Point
from std_msgs.msg import String # Ajouté le 16/04 à 12h35

import rtde_control
import rtde_receive
from scipy.spatial.transform import Rotation as R
import math
import threading
import time # Déplacé le 15/04

from rcl_interfaces.msg import SetParametersResult # Ajouté le 16/04 à 17h00 -- pour les paramètres dynamiques

class TestUnityP1(Node):
    def __init__(self):
        super().__init__('test_unity_p1')

        self.rc = rtde_control.RTDEControlInterface("192.168.1.101")
        self.rr = rtde_receive.RTDEReceiveInterface("192.168.1.101")

        # Position initiale
        self.init_pose = [
            math.radians(-45),
            #math.radians(-135),
            math.radians(-90),
            math.radians(90),
            math.radians(-180),
            math.radians(-90),
            math.radians(180),
        ]

        self.get_logger().info("Déplacement vers position initiale...") #Ajouté le 15/04

        # Aller en position initiale + calculer z_axis_in_base et orientation
        # self.rc.moveJ(self.init_pose, 0.1, 0.1)
        self.rc.moveJ(self.init_pose, 0.5, 0.5) # vitesse plus élevée
        
        self.get_logger().info("Position initiale atteinte.") #Ajouté le 15/04

        #Récupérer les coordonnées(POSITION + ROTATION) du vecteur Z_TCP dans le repère base
        tcp = self.rr.getActualTCPPose()
        self.orientation = [tcp[3], tcp[4], tcp[5]]
        rot = R.from_rotvec(tcp[3:6])
        self.z_axis_in_base = rot.as_matrix()[:, 2]

        self.error_event = threading.Event()

        #Ajouté le 16/04 à 12h35
        self.abort_active = False

        #Ajouté je 16/04 à 16h45
        self.declare_parameter('force_target', 20.0)
        self.declare_parameter('force_wrench', 50.0)
        self.declare_parameter('force_max', 70.0)
        self.declare_parameter('scenario_mode', 0)
        self.declare_parameter('timeout', 30.0)
        self.declare_parameter('offset', 0.1)
        self.declare_parameter('xy_norm_min', 0.230)
        self.declare_parameter('settle_time', 0.2)
        self.declare_parameter('bias_samples', 50)
        self.declare_parameter('bias_std_threshold', 0.5)
        self.declare_parameter('hold_time', 0.5) # Ajouté le 17/04 à 11h40

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

        self.get_logger().info(f"Position initiale TCP : x:{tcp[0]*1000:.2f}mm  y:{tcp[1]*1000:.2f}mm  z:{tcp[2]*1000:.2f}mm")  # Afficher pose TCP dans repère base

        self.get_logger().info(f"Z axis in base : x:{self.z_axis_in_base[0]:.4f}  y:{self.z_axis_in_base[1]:.4f}  z:{self.z_axis_in_base[2]:.4f}") # Afficher coords vecteur Z_TCP dans repère base

        self.create_subscription(Point, 'cube_position', self.cb_p1, 10) # S'abonner au topic pour recevoir la pose du cube (point de toucher)
        self.get_logger().info("En attente de P1 depuis Unity...")

    def cb_p1(self, msg):
        P1 = [msg.x, msg.y, msg.z]
        self.get_logger().info(f"P1 reçu : x={P1[0]:.4f}  y={P1[1]:.4f}  z={P1[2]:.4f}")
        t = threading.Thread(target=self.move_to_p1, args=(P1,))
        t.start()

    #Ajouté le 16/04 à 12h35
    def cb_abort(self, msg):
        self.abort_active = True
        self.get_logger().error(f"SAFETY ABORT reçu : {msg.data}")

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

    def move_to_p1(self, P1):
        # Aller directement en P1 pour vérifier calibration Unity <-> robot réel #JUSTE POUR VERIFIER
        # self.rc.moveL([P1[0], P1[1], P1[2],
        #                self.orientation[0], self.orientation[1], self.orientation[2]],
        #                0.05, 0.05)
        # tcp = self.rr.getActualTCPPose()
        # self.get_logger().info(f"En P1 ! TCP réel : x:{tcp[0]*1000:.2f}mm  y:{tcp[1]*1000:.2f}mm  z:{tcp[2]*1000:.2f}mm")


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

        # Ajouté le 17/04 à 11h25
        if self.scenario_mode == 0:  # Push
            offset = self.offset
            wrench = [0, 0, self.force_wrench, 0, 0, 0]
        elif self.scenario_mode == 1:  # Punch
            offset = self.offset
            wrench = [0, 0, min(self.force_wrench * 2, 150), 0, 0, 0]
        elif self.scenario_mode == 2:  # Touch
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

        ### Ajouté le 16/04 pour les limites avec la norme ###
        xy_norm = math.sqrt(pre_P1[0]**2 + pre_P1[1]**2)
        self.get_logger().info(f"Norme XY pre_P1 = {xy_norm*1000:.1f}mm") # Afficher la norme

        # testé empiriquement valeur trouvé
        # if xy_norm < 0.2265:
        #     self.get_logger().warn(f"pre_P1 trop proche de la base (norme XY = {xy_norm*1000:.1f}mm < 226.5mm) — renvoyer un autre point.")
        #     return
        
        # valeur repoussé à 230 pour plus de sûreté
        if xy_norm < self.xy_norm_min:
            ############################
            msg = String()
            msg.data = "aborted"
            self.status_pub.publish(msg)
            ############################
            self.get_logger().warn(f"pre_P1 trop proche de la base (norme XY = {xy_norm*1000:.1f}mm < 230mm) — renvoyer un autre point.")
            return

        #################################

        # self.rc.moveL(pre_P1, 0.05, 0.05)
        # print(f"En pre_P1 !")

        #Ajouté le 16/04 à 15h15#######################
        self.rc.moveL(pre_P1, 0.05, 0.05, asynchronous=True)
        while self.rc.getAsyncOperationProgress() >= 0:
            if self.abort_active:
                self.rc.stopL(0.5)
                ############################
                msg = String()
                msg.data = "aborted"
                self.status_pub.publish(msg)
                ############################
                self.get_logger().error("Abort reçu pendant moveL — arrêt immédiat.")
                return
            time.sleep(0.02)
        print(f"En pre_P1 !")
        ###############################################

        # ETAPE force mode : pousser en Z TCP vers P1
        
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
        ###############################################################################


        tcp_current = self.rr.getActualTCPPose()
        task_frame = list(tcp_current) # repère de poussée
        selection_vector = [0, 0, 1, 0, 0, 0] # quel axe ?
        # wrench = [0, 0, self.force_wrench, 0, 0, 0] # force de poussée


        limits = [2, 2, 1.5, 1, 1, 1] # ??
        t_start_loop = time.time()
        TIMEOUT = self.timeout # temps avant mort
        #FORCE_TARGET = self.force_target # force cible

        # Ajouté le 17/04 à 11h15
        if self.scenario_mode == 2:  # Touch
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
            if runtime_state != 2:
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
                print(f"Force cible atteinte : {force_dev:.2f}N !")
                if self.scenario_mode == 0:  # Push
                    self.get_logger().info("Mode Push — maintien 2s...")
                    # time.sleep(2.0)
                    time.sleep(self.hold_time)
                    self.rc.forceModeStop()
                    retract_speed, retract_accel = 0.2, 0.5
                elif self.scenario_mode == 1:  # Punch
                    self.rc.forceModeStop()
                    self.get_logger().info("Mode Punch — rétraction rapide !")
                    retract_speed, retract_accel = 1.0, 2.0
                elif self.scenario_mode == 2:  # Touch
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
        
        # Commenté le 17/04 à 11h00
        # self.rc.forceModeStop()
        # print("Force mode OFF")

        # ETAPE retraction : retour position initiale
        # self.rc.moveJ(self.init_pose, 0.1, 0.1)
        # print("Retour position initiale !")

        # # Commenté le 16/04 à 15h15
        # self.rc.moveL(pre_P1, 0.2, 0.5)
        # print(f"Rétracté en pre_P1 !")

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
            time.sleep(0.02)
        print(f"Rétracté en pre_P1 !")
        #########################################

        # Ajouté 17/04 à 13h10
        msg = String()
        msg.data = "ready"
        self.status_pub.publish(msg)
        self.get_logger().info("Statut : ready — en attente du prochain PLAY.")

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
    while True:
        try:
            node = TestUnityP1()
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
            print(f"[ERREUR] {e}") # Modifié le 16/04 -- Afficher l'erreur exacte
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