import numpy as np
import matplotlib.pyplot as plt
import csv

x = []
pressure = []
temperature = []
velocity = []
mach = []

with open('data.csv') as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    for row in csv_reader:
        x.append(float(row[0]))
        pressure.append(float(row[1]))
        temperature.append(float(row[2]))
        velocity.append(float(row[3]))
        mach.append(float(row[4]))

x = np.array(x)
pressure = np.array(pressure)
temperature = np.array(temperature)
velocity = np.array(velocity)
mach = np.array(mach)

pressure = pressure/max(pressure)
temperature = temperature/max(temperature)
velocity = velocity/max(velocity)
mach = mach/max(mach)

plt.plot(x, pressure, '-.')
plt.plot(x, temperature, '-.')
plt.plot(x, velocity, '-.')
plt.plot(x, mach, '-.')
plt.legend(['Pressure', 'Temperature', 'Velocity', 'Mach'])
plt.show()