#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

// Making a new structure for storing grid and iteration counts
struct grid
{
    double grid[41][21];
    int iteration_count;
};

// For printing out a grid
void printGrid(struct grid grid)
{
    for (int i = 0; i < 41; i++)
    {
        for (int j = 0; j < 21; j++)
        {
            printf("%f ", grid.grid[i][j]);
        }
        printf("\n");
    }
}

// Applying boudary conditions to the grid
struct grid initialCondition()
{
    struct grid grid;

    for (int i = 0; i < 41; i++)
    {
        for (int j = 0; j < 21; j++)
        {
            grid.grid[i][j] = 0;
        }
    }

    for (int j = 0; j < 21; j++)
    {
        grid.grid[40][j] = 100;
    }

    return grid;
}

// Finding out the error in this and previous grids
double error_iteration(struct grid newGrid, struct grid grid)
{
    double error = 0;
    for (int i = 1; i < 40; i++)
    {
        for (int j = 1; j < 20; j++)
        {
            error += fabs(newGrid.grid[i][j] - grid.grid[i][j]);
        }
    }
    return error;
}

// Point Jacobi Main Code
struct grid pointJacobi(struct grid grid, double beta)
{
    struct grid newGrid;
    newGrid = initialCondition();

    for (int i = 39; i > 0; i--)
    {
        for (int j = 1; j < 20; j++)
        {
            newGrid.grid[i][j] = (1 / (2 * (1 + beta * beta))) * (grid.grid[i + 1][j] + grid.grid[i - 1][j] + beta * beta * grid.grid[i][j + 1] + beta * beta * grid.grid[i][j - 1]);
        }
    }

    return newGrid;
}

// Point Gauss-Seidel Main Code
struct grid pointGS(struct grid grid, double beta)
{
    struct grid newGrid;
    newGrid = initialCondition();

    for (int i = 39; i > 0; i--)
    {
        for (int j = 1; j < 20; j++)
        {
            newGrid.grid[i][j] = (1 / (2 * (1 + beta * beta))) * (newGrid.grid[i + 1][j] + grid.grid[i - 1][j] + beta * beta * grid.grid[i][j + 1] + beta * beta * newGrid.grid[i][j - 1]);
        }
    }

    return newGrid;
}

// Point Succesive Over Relaxation Main Code
struct grid pointSOR(struct grid grid, double beta, double w)
{
    struct grid newGrid;
    newGrid = initialCondition();

    for (int i = 39; i > 0; i--)
    {
        for (int j = 1; j < 20; j++)
        {
            newGrid.grid[i][j] = grid.grid[i][j] + w * ((1 / (2 * (1 + beta * beta))) * (newGrid.grid[i + 1][j] + grid.grid[i - 1][j] + beta * beta * grid.grid[i][j + 1] + beta * beta * newGrid.grid[i][j - 1] - 2 * (1 + beta * beta) * grid.grid[i][j]));
        }
    }

    return newGrid;
}

// Iterations are happening here
struct grid iterations(struct grid grid, double beta, int method, double w)
{
    struct grid newGrid;
    newGrid = initialCondition();

    double error;

    int count = 0;

    while (true)
    {

        if (method == 1)
        {
            newGrid = pointJacobi(grid, beta);
        }
        else if (method == 2)
        {
            newGrid = pointGS(grid, beta);
        }
        else if (method == 3)
        {
            newGrid = pointSOR(grid, beta, w);
        }

        error = error_iteration(newGrid, grid);

        if (error < 0.01)
        {
            break;
        }

        grid = newGrid;
        count++;
    }

    newGrid.iteration_count = count;

    return newGrid;
}

// Final solution
struct grid solutions(int method)
{
    FILE *fptr;

    struct grid grid;
    struct grid finalGrid;
    double beta = 1;

    grid = initialCondition();

    finalGrid = iterations(grid, beta, method, 1.78);

    fptr = fopen("temp.csv", "w");
    for (int i = 0; i < 41; i++)
    {
        for (int j = 0; j < 21; j++)
        {
            if (j != 20)
            {
                fprintf(fptr, "%f,", finalGrid.grid[i][j]);
            }
            else
            {
                fprintf(fptr, "%f\n", finalGrid.grid[i][j]);
            }
        }
    }
    fclose(fptr);
    return finalGrid;
}

// Convergence History
void convergenceHistory()
{
    FILE *fptr;

    struct grid grid;
    struct grid finalGrid;
    double beta = 1;

    grid = initialCondition();

    double error;

    int count = 0;
    fptr = fopen("error.csv", "w");

    while (true)
    {
        finalGrid = pointJacobi(grid, beta);
        error = error_iteration(finalGrid, grid);
        if (error < 0.01)
        {
            break;
        }

        fprintf(fptr, "%f, %d\n", error, count);

        grid = finalGrid;
        count++;
    }

    fprintf(fptr, "pgs\n");
    count = 0;
    grid = initialCondition();

    while (true)
    {
        finalGrid = pointGS(grid, beta);
        error = error_iteration(finalGrid, grid);
        if (error < 0.01)
        {
            break;
        }

        fprintf(fptr, "%f, %d\n", error, count);

        grid = finalGrid;
        count++;
    }

    fprintf(fptr, "psor\n");
    count = 0;
    grid = initialCondition();

    while (true)
    {
        finalGrid = pointSOR(grid, beta, 1.78);
        error = error_iteration(finalGrid, grid);
        if (error < 0.01)
        {
            break;
        }

        fprintf(fptr, "%f, %d\n", error, count);

        grid = finalGrid;
        count++;
    }

    fclose(fptr);
}

// Finding Total Number of steps
void numberSteps()
{
    struct grid grid;
    struct grid finalGrid;
    double beta = 1;

    grid = initialCondition();
    finalGrid = iterations(grid, beta, 1, 1.784);
    printf("Point Jacobi - %d\n", finalGrid.iteration_count);

    grid = initialCondition();
    finalGrid = iterations(grid, beta, 2, 1.784);
    printf("Point GS - %d\n", finalGrid.iteration_count);

    grid = initialCondition();
    finalGrid = iterations(grid, beta, 3, 1.784);
    printf("Point SOR - %d\n", finalGrid.iteration_count);
}

// Finding out the optimum w
void optimumW()
{
    FILE *fptr;

    struct grid grid;
    struct grid finalGrid;
    double beta = 1;

    grid = initialCondition();

    fptr = fopen("optimum_w.csv", "w");

    for (double i = 50; i < 100; i++)
    {
        double w = i / 50;
        finalGrid = iterations(grid, beta, 3, w);
        fprintf(fptr, "%f, %d\n", w, finalGrid.iteration_count);
        // printf("%d iterations for w = %f\n", finalGrid.iteration_count, w);
    }
    fclose(fptr);
}

// The exact solution
struct grid exactSolution()
{
    FILE *fptr = fopen("real.csv", "w");
    struct grid finalGrid = initialCondition();

    double T = 0;

    for (double i = 1; i < 40; i++)
    {
        T = 0;
        for (double n = 1; n < 99; n = n + 2)
        {
            T += 2 / (n * M_PI) * (sinh(n * M_PI * (2 - (i) / 20)) * sin(n * M_PI * 0.5)) / (sinh(n * M_PI * 2));
        }
        int itr = i;
        finalGrid.grid[40 - itr][10] = T * 200;
    }

    for (double j = 1; j < 20; j++)
    {
        T = 0;
        for (double n = 1; n < 100; n = n + 2)
        {
            T += 2 / (n * M_PI) * (sinh(n * M_PI) * sin(n * M_PI * (j / 20))) / (sinh(n * M_PI * 2));
        }
        int itr = j;
        finalGrid.grid[20][itr] = T * 200;
    }

    for (int i = 0; i < 41; i++)
    {
        for (int j = 0; j < 21; j++)
        {
            if (j != 20)
            {
                fprintf(fptr, "%f,", finalGrid.grid[i][j]);
            }
            else
            {
                fprintf(fptr, "%f\n", finalGrid.grid[i][j]);
            }
        }
    }
    fclose(fptr);

    return finalGrid;
}

// Main Function (controlled by the shell script (final.sh))
int main(int argc, char *argv[])
{
    if (atoi(argv[1]) == 1)
    {
        convergenceHistory();
    }
    else if (atoi(argv[1]) == 2)
    {
        numberSteps();
    }
    else if (atoi(argv[1]) == 3)
    {
        optimumW();
    }
    else if (atoi(argv[1]) == 4)
    {
        exactSolution();
        solutions(atoi(argv[2]));
    }
    else if (atoi(argv[1]) == 5)
    {
        solutions(atoi(argv[2]));
    }
}