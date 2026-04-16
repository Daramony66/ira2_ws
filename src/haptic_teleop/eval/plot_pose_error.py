import matplotlib.pyplot as plt
import numpy as np

data = np.loadtxt('latencies_errors.csv', delimiter=',')

pos_errors = data[:, 0]
ori_errors = data[:, 1]

plt.figure(figsize=(12, 6))
plt.plot(pos_errors, label='Erreur de position (m)', color='blue')
plt.plot(ori_errors, label='Erreur d\'orientation (rad)', color='red')
plt.xlabel('Échantillon')
plt.ylabel('Erreur')
plt.title('Erreurs de suivi de la pose')
plt.grid(True)
plt.legend()
plt.show()