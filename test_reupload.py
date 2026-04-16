import rtde_control
import time

print("Connexion RTDE...")
r = rtde_control.RTDEControlInterface('192.168.1.101')
print("Connecté !")

print("Reupload script...")
r.reuploadScript()
print("Done !")