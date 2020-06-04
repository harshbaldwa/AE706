#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

// Find the maximum of two numbers
double max (double a, double b) {
    return (a > b) ? a : b;
}

// Structure for the U matrix
struct uMatrix {
    double u[3][103];
};

// Structure for the F matrices
struct fMatrices {
    double fPlus[3][103];
    double fMinus[3][103];
};

// Sets the initial conditions as per the question given
struct uMatrix initialConditions() {
    struct uMatrix u;

    double velocity = 0;
    double temperature = 300;
    double pressureLeft = 5;
    double pressureRight = 1;

    double r = 287.1;
    double gamma = 1.4;
    double densityLeft = pressureLeft/(r*temperature);
    double densityRight = pressureRight/(r*temperature);
    double energyLeft = pressureLeft/(gamma - 1) + densityLeft*velocity*velocity/2;
    double energyRight = pressureRight/(gamma - 1) + densityRight*velocity*velocity/2;

    for (int i=0; i<51; i++) {
        u.u[0][i] = densityLeft;
        u.u[1][i] = densityLeft*velocity;
        u.u[2][i] = energyLeft;
    }

    for (int i=51; i<103; i++) {
        u.u[0][i] = densityRight;
        u.u[1][i] = densityRight*velocity;
        u.u[2][i] = energyRight;
    }

    return u;
}

// Calculating the timestep as per the current conditions
double timeStep (struct uMatrix u) {
    double lambda = 0;
    double dx = 0.01;
    double cflNumber = 0.8;
    double gamma = 1.4;

    for (int i=1; i<102; i++) {
        double velocity = u.u[1][i] / u.u[0][i];
        double pressure = (u.u[2][i] - u.u[0][i]*velocity*velocity/2)*(gamma - 1);
        double a = sqrt(pressure*gamma/u.u[0][i]);
        double temp = max(lambda, a+fabs(velocity));
        lambda = temp;
    }

    return cflNumber*dx/lambda;
}

// Calculating the F matrices as per the Mach Number
struct fMatrices calculateFMatrices(struct uMatrix u) {
    struct fMatrices f;
    double gamma = 1.4;

    for (int i=0; i<103; i++) {
        double velocity = u.u[1][i] / u.u[0][i];
        double pressure = (u.u[2][i] - u.u[0][i] * velocity * velocity / 2) * (gamma - 1);
        double a = sqrt(pressure * gamma / u.u[0][i]);
        double m = velocity/a;
        if (m <= -1) {
            f.fPlus[0][i] = 0;
            f.fPlus[1][i] = 0;
            f.fPlus[2][i] = 0;
            f.fMinus[0][i] = u.u[1][i];
            f.fMinus[1][i] = u.u[1][i]*velocity + pressure;
            f.fMinus[2][i] = (u.u[2][i]+pressure)*velocity;
        } else if (m > -1 && m <= 0) {
            double scalePlus = u.u[0][i]*(velocity + a)/(2*gamma);
            double scaleMinus1 = (gamma - 1)*u.u[0][i]*velocity/gamma;
            double scaleMinus2 = u.u[0][i]*(velocity - a)/(2 * gamma);
            f.fPlus[0][i] = scalePlus;
            f.fPlus[1][i] = scalePlus*(velocity + a);
            f.fPlus[2][i] = scalePlus*(velocity*velocity/2 + a*a/(gamma-1) + velocity*a);
            f.fMinus[0][i] = scaleMinus1 + scaleMinus2;
            f.fMinus[1][i] = scaleMinus1*velocity + scaleMinus2*(velocity - a);
            f.fMinus[2][i] = scaleMinus1*(velocity*velocity/2) + scaleMinus2*(velocity*velocity/2 + a*a/(gamma-1) - velocity*a);
        } else if (m > 0 && m <= 1) {
            double scalePlus1 = (gamma - 1)*u.u[0][i]*velocity/gamma;
            double scalePlus2 = u.u[0][i]*(velocity + a)/(2*gamma);
            double scaleMinus = u.u[0][i]*(velocity - a)/(2*gamma);
            f.fPlus[0][i] = scalePlus1 + scalePlus2;
            f.fPlus[1][i] = scalePlus1*velocity + scalePlus2*(velocity + a);
            f.fPlus[2][i] = scalePlus1*(velocity*velocity/2) + scalePlus2*(velocity*velocity/2 + a*a/(gamma-1) + velocity*a);
            f.fMinus[0][i] = scaleMinus;
            f.fMinus[1][i] = scaleMinus*(velocity - a);
            f.fMinus[2][i] = scaleMinus*(velocity*velocity/2 + a*a/(gamma-1) - velocity*a);
        } else {
            f.fPlus[0][i] = u.u[1][i];
            f.fPlus[1][i] = u.u[1][i]*velocity + pressure;
            f.fPlus[2][i] = (u.u[2][i]+pressure)*velocity;
            f.fMinus[0][i] = 0;
            f.fMinus[1][i] = 0;
            f.fMinus[2][i] = 0;
        }
    }

    return f;
}

// updating the U matrix
struct uMatrix iteration (struct uMatrix u, double dt) {
    struct uMatrix uNPlus;
    double dx = 0.01;
    struct fMatrices f = calculateFMatrices(u);
    for (int i=1; i<102; i++) {
        uNPlus.u[0][i] = u.u[0][i] - dt*(f.fPlus[0][i] - f.fPlus[0][i-1])/dx - dt*(f.fMinus[0][i+1] - f.fMinus[0][i])/dx;
        uNPlus.u[1][i] = u.u[1][i] - dt*(f.fPlus[1][i] - f.fPlus[1][i-1])/dx - dt*(f.fMinus[1][i+1] - f.fMinus[1][i])/dx;
        uNPlus.u[2][i] = u.u[2][i] - dt*(f.fPlus[2][i] - f.fPlus[2][i-1])/dx - dt*(f.fMinus[2][i+1] - f.fMinus[2][i])/dx;
    }
    uNPlus.u[0][0] = uNPlus.u[0][1];
    uNPlus.u[1][0] = uNPlus.u[1][1];
    uNPlus.u[2][0] = uNPlus.u[2][1];

    uNPlus.u[0][102] = uNPlus.u[0][101];
    uNPlus.u[1][102] = uNPlus.u[1][101];
    uNPlus.u[2][102] = uNPlus.u[2][101];

    return uNPlus;
}

// Loop
void solution () {
    struct uMatrix u = initialConditions();
    double time = 0;
    double timeFinal = 0.00075;
    struct uMatrix uNPlus;
    double dt = 0;
    int count = 0;

    FILE *fptr;

    while (time < timeFinal) {
        dt = timeStep(u);
        uNPlus = iteration(u, dt);
        u = uNPlus;
        time += dt;
        count += 1;
    }

    // saving the data in a csv file and used this data to plot using python
    fptr = fopen("data.csv", "w");
    double x = 0;
    double pressure = 0;
    double temperature = 0;
    double velocity = 0;
    double mach = 0;
    double gamma = 1.4;

    for (int i=1; i<102; i++) {
        x = (i - 1) * 0.01;
        velocity = uNPlus.u[1][i] / uNPlus.u[0][i];
        pressure = (uNPlus.u[2][i] - uNPlus.u[0][i] * velocity * velocity / 2) * (gamma - 1);
        temperature = pressure/(287.1*uNPlus.u[0][i]);
        mach = velocity/sqrt(gamma*287.1*temperature);

        fprintf(fptr, "%f, %f, %f, %f, %f\n", x, pressure, temperature, velocity, mach);
    }
}
int main () {
    solution();
    return 0; 
}

