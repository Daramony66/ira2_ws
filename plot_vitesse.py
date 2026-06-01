import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

df = pd.read_csv('/home/stlab24-04/ira2_ws/vitesse_data.csv')

fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(10, 10))

for essai in sorted(df['essai'].unique()):
    data = df[df['essai'] == essai].copy()
    wrench = data['wrench_N'].iloc[0]
    ax1.plot(data['temps'], data['vitesse_mm_s'], label=f'essai {essai} ({wrench}N)')
    accel = np.gradient(data['vitesse_mm_s'].values, data['temps'].values)
    ax2.plot(data['temps'], accel, label=f'essai {essai} ({wrench}N)')

#AFFICHAGE DE LA VMAX GLOBALE
vmax_global = df['vitesse_mm_s'].max()
ax1.axhline(y=vmax_global, linestyle='--', color='red', label=f'vmax globale : {vmax_global:.1f} mm/s')

ax1.set_xlabel('Temps (s)')
ax1.set_ylabel('Vitesse TCP (mm/s)')
ax1.set_title('Vitesse TCP en fonction du temps selon le wrench')
ax1.legend()
ax1.grid(True)

ax2.set_xlabel('Temps (s)')
ax2.set_ylabel('Accélération TCP (mm/s²)')
ax2.set_title('Accélération TCP en fonction du temps selon le wrench')
ax2.legend()
ax2.grid(True)

plt.tight_layout()
plt.savefig('/home/stlab24-04/ira2_ws/courbes_vitesse_accel.png')
plt.show()