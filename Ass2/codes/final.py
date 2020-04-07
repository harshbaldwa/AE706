import matplotlib.pyplot as plt
import numpy as np
import csv

def contour_plotting():
    temp = []

    with open('temp.csv') as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        for row in csv_reader:
            temp.append([float(i) for i in row])

    temp = np.array(temp)
    x = np.linspace(0, 21, 21)
    y = np.linspace(0, 41, 41)

    plt.contourf(x[::-1], y[::-1], temp, 100)
    plt.colorbar()
    plt.show()

def error_iterations():

    error_PJ = []
    error_PGS = []
    error_PSOR = []

    iterations_PJ = []
    iterations_PGS = []
    iterations_PSOR = []

    with open('error.csv') as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        pj = True
        pgs = False
        psor = False
        
        for row in csv_reader:
            if row[0] == 'pgs':
                pgs = True
            if row[0] == 'psor':
                psor = True

            if pj == True and pgs != True and psor != True:
                error_PJ.append(float(row[0]))
                iterations_PJ.append(float(row[1]))
            
            if pj == True and pgs == True and psor != True and row[0] != 'pgs':
                error_PGS.append(float(row[0]))
                iterations_PGS.append(float(row[1]))

            if pj == True and pgs == True and psor == True and row[0] != 'psor':
                error_PSOR.append(float(row[0]))
                iterations_PSOR.append(float(row[1]))
        
    plt.plot(iterations_PJ, error_PJ)
    plt.plot(iterations_PGS, error_PGS)
    plt.plot(iterations_PSOR, error_PSOR)
    plt.legend(['PJ', 'PGS', 'PSOR'])
    plt.title('Convergence History')
    plt.yscale('log')
    plt.ylabel('Error')
    plt.xlabel('Iterations')
    plt.show()

def optimum_w():
    w = []
    iterations = []

    with open('optimum_w.csv') as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        for row in csv_reader:
            w.append(float(row[0]))
            iterations.append(float(row[1]))

    print("Minimum w is " + str(w[iterations.index(min(iterations))]))
    plt.plot(w, iterations)
    # plt.yscale('log')
    plt.ylabel('W (correction factor)')
    plt.xlabel('Iterations')
    plt.title('Optimum W for PSOR')
    plt.show()

def plot_result_midlines():
    temp = []
    temp_real = []

    with open('temp.csv') as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        for row in csv_reader:
            temp.append([float(i) for i in row])

    with open('real.csv') as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        for row in csv_reader:
            temp_real.append([float(i) for i in row])

    temp = np.array(temp)
    temp_real = np.array(temp_real)
    x = np.linspace(0, 21, 21)
    y = np.linspace(0, 41, 41)
    _, ax = plt.subplots(1,2)
    ax[0].plot(x, temp[20, :], label="calculated")
    ax[0].plot(x, temp_real[20,:],'.', label="real")
    ax[0].set_title('Along constant y')
    ax[0].legend()
    ax[1].plot(y[::-1], temp[:, 10], label="calculated")
    ax[1].plot(y[::-1], temp_real[:, 10], '.', label="real")
    ax[1].set_title('Along constant x')
    ax[1].legend()
    plt.show()
