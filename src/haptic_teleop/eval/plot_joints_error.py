import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

file_path = "joint_errors.csv"
data = pd.read_csv(file_path)

time = data['time']
joints = ['joint_1', 'joint_2', 'joint_3', 'joint_4', 'joint_5', 'joint_6']
errors = {joint: data[joint] for joint in joints}

# Calculer la moyenne et l'écart-type pour chaque joint
stats = {joint: {'mean': np.mean(errors[joint]), 'std': np.std(errors[joint])} for joint in joints}

# Afficher les statistiques
print("Statistiques des erreurs (en radians) :")
for joint in joints:
    print(f"{joint}: Moyenne = {stats[joint]['mean']:.4f}, Écart-type = {stats[joint]['std']:.4f}")
    
plt.figure(figsize=(12, 8))

for joint in joints:
    plt.plot(time, errors[joint], label=f'{joint} error', linewidth=1.5)


plt.title('Erreur articulaire en fonction du temps', fontsize=14)
plt.xlabel('Temps (s)', fontsize=12)
plt.ylabel('Erreur (rad)', fontsize=12)
plt.legend()
plt.grid(True, linestyle='--', alpha=0.7)


plt.ylim(-0.2, 0.2)  
plt.show()