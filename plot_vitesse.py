import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('/home/stlab24-04/ira2_ws/vitesse_data.csv')

plt.figure(figsize=(10, 6))
for wrench in sorted(df['wrench_N'].unique()):
    data = df[df['wrench_N'] == wrench]
    plt.plot(data['temps'], data['vitesse_mm_s'], label=f'{wrench}N')

plt.xlabel('Temps (s)')
plt.ylabel('Vitesse TCP (mm/s)')
plt.title('Vitesse TCP en fonction du temps selon le wrench')
plt.legend()
plt.grid(True)
plt.savefig('/home/stlab24-04/ira2_ws/courbes_vitesse.png')
plt.show()
