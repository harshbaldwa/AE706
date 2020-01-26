from matplotlib import pyplot as plt
import matplotlib.animation as animation
import csv

fig = plt.figure()
plt.xlim(0, 1)
plt.ylim(-1.5, 1.5)

time = []
ampOut = []

lines = [plt.plot([], [])[0] for _ in range(101)]

for i in range(101):
    time.append(i/101)


def init():
    #init lines
    for line in lines:
        line.set_data([], [])

    return lines

name = ''

with open('out.csv') as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    count = 0
    for row in csv_reader:
        if count == 0:
            name = row[0]
        elif count == 1:
            count = 1
        else :
            amp = []
            for i in range(101):
                amp.append(float(row[i]))
            ampOut.append(amp)
        count += 1

def update(num):
    for line in lines:
        line.set_xdata(time)
        line.set_ydata(ampOut[num])
    return lines

print(name + ' animation started!')

line_ani = animation.FuncAnimation(fig, update, 99,
                                   interval=50, blit=True)

line_ani.save('animations/' + name + '.mp4')

print(name + ' animation done!')
