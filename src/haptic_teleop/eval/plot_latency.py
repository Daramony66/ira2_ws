import matplotlib.pyplot as plt
import numpy as np

data = np.loadtxt('latencies.csv')

plt.figure(figsize=(10, 6))
plt.plot(data, label='Latence (secondes)')
plt.xlabel('Échantillon')
plt.ylabel('Latence (s)')
plt.title('Latence du système entre envoi et exécution')
plt.grid(True)
plt.legend()
plt.show()