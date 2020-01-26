import csv
import matplotlib.pyplot as plt

time = []
amp = []
name = ''

with open('file.csv') as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    count = 0
    for row in csv_reader:
        if count == 0:
            name = row[0]
        else:
            T = float(row[0])
            A = float(row[1])

            time.append(T)
            amp.append(A)
        count += 1


plt.plot(time,amp)
axes = plt.gca()
plt.title(name)
axes.set_xlim([0, 1])
axes.set_ylim([-1.5, 1.5])
plt.show()
# plt.savefig(name+'.png')
