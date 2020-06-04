import numpy as np
import matplotlib.pyplot as plt
import csv

x = []
pressure = []
temperature = []
velocity = []
mach = []
exact_x = []
exact_pressure = []
exact_temperature = []
exact_velocity = []
exact_mach = []

with open('data.csv') as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    for row in csv_reader:
        x.append(float(row[0]))
        pressure.append(float(row[1]))
        temperature.append(float(row[2]))
        velocity.append(float(row[3]))
        mach.append(float(row[4]))

with open('data_real.csv') as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    for row in csv_reader:
        exact_x.append(float(row[0]))
        exact_pressure.append(float(row[1]))
        exact_temperature.append(float(row[2]))
        exact_velocity.append(float(row[3]))
        exact_mach.append(float(row[4]))

x = np.array(x)
pressure = np.array(pressure)
temperature = np.array(temperature)
velocity = np.array(velocity)
mach = np.array(mach)

exact_x = np.array(exact_x)
exact_pressure = np.array(exact_pressure)
exact_temperature = np.array(exact_temperature)
exact_velocity = np.array(exact_velocity)
exact_mach = np.array(exact_mach)

pressure = pressure / max(pressure)
temperature = temperature / max(temperature)
velocity = velocity / max(velocity)
mach = mach / max(mach)

exact_pressure = exact_pressure / max(exact_pressure)
exact_temperature = exact_temperature / max(exact_temperature)
exact_velocity = exact_velocity / max(exact_velocity)
exact_mach = exact_mach / max(exact_mach)

fig, ax = plt.subplots(2,2)

ax[0, 0].plot(exact_x, exact_pressure, 'g-')
ax[0, 0].plot(x, pressure, 'y.')
ax[0, 0].set_ylabel('p')

ax[0, 1].plot(exact_x, exact_temperature, 'g-')
ax[0, 1].plot(x, temperature, 'y.')
ax[0, 1].set_ylabel('T')


ax[1, 0].plot(exact_x, exact_velocity, 'g-')
ax[1, 0].plot(x, velocity, 'y.')
ax[1, 0].set_ylabel('u')

ax[1, 1].plot(exact_x, exact_mach, 'g-')
ax[1, 1].plot(x, mach, 'y.')
ax[1, 1].set_ylabel('M')

fig.legend(['Analytical', 'Solver'])
plt.show()