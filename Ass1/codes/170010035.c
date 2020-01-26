#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

void case1(double *array) {
    for (int i=0; i<101; i++) {
        if (i<21) {
            array[i] = 1;
        } else {
            array[i] = 0;
        }
    }
}

void case2(double *array) {
    for (int i=0; i<101; i++) {
        if (i<5) {
            array[i] = 0;
        } else if (i>=5 && i<35) {
            array[i] = sin(4*M_PI*(i-5)/30);
        } else {
            array[i] = 0;
        }
    }
}

void case3(double *array) {
    for (int i=0; i<101; i++) {
        if (i<5) {
            array[i] = 0;
        } else if (i>=5 && i<35) {
            array[i] = sin(8*M_PI*(i-5)/30);
        } else {
            array[i] = 0;
        }
    }
}

void case4(double *array) {
    for (int i=0; i<101; i++) {
        if (i<5) {
            array[i] = 0;
        } else if (i>=5 && i<35) {
            array[i] = sin(12*M_PI*(i-5)/30);
        } else {
            array[i] = 0;
        }
    }
}

void FTFS(double *initialCondArr, int T, double mu, FILE *fPtr, int caseNo) {
    double nextArr[101];

    fPtr = fopen("file.csv", "w");

    for (int t = 0; t < T; t++) {
        for (int i = 0; i < 100; i++) {
            nextArr[i] = initialCondArr[i] - mu * (initialCondArr[i + 1] - initialCondArr[i]);
        }
        for (int h = 0; h < 100; h++) {
            initialCondArr[h] = nextArr[h];
        }
        initialCondArr[100] = nextArr[99];
        nextArr[100] = nextArr[99];
    }

    fprintf(fPtr, "FTFS - %d - %.2f @ T = %d \n", caseNo, mu, T);

    for (int i=0; i<101; i++) {
        double z = i; 
        fprintf(fPtr, "%f, %f \n", z/101, nextArr[i]);
    }

    fclose(fPtr);
}

void FTCS(double *initialCondArr, int T, double mu, FILE *fPtr, int caseNo) {
    double nextArr[101];

    fPtr = fopen("file.csv", "w");

    for (int t = 0; t < T; t++) {
        for (int i = 1; i < 100; i++) {
            nextArr[i] = initialCondArr[i] - (mu/2)*(initialCondArr[i+1] - initialCondArr[i-1]);
        }
        for (int h = 1; h < 100; h++) {
            initialCondArr[h] = nextArr[h];
        }
        initialCondArr[0] = 0;
        initialCondArr[100] = nextArr[99];
        nextArr[0] = 0;
        nextArr[100] = nextArr[99];
    }

    fprintf(fPtr, "FTCS - %d - %.2f @ T = %d \n ", caseNo, mu, T);

    for (int i=0; i<101; i++) {
        double z = i; 
        fprintf(fPtr, "%f, %f \n", z/101, nextArr[i]);
    }

    fclose(fPtr);
}

void FTBS(double *initialCondArr, int T, double mu, FILE *fPtr, int caseNo) {
    double nextArr[101];

    fPtr = fopen("file.csv", "w");

    for (int t = 0; t < T; t++) {
        for (int i = 1; i < 101; i++) {
            nextArr[i] = initialCondArr[i] - mu*(initialCondArr[i] - initialCondArr[i-1]);
        }
        for (int h = 1; h < 101; h++) {
            initialCondArr[h] = nextArr[h];
        }
        nextArr[0] = nextArr[1];
        initialCondArr[0] = 0;
    }

    fprintf(fPtr, "FTBS - %d - %.2f @ T = %d \n ", caseNo, mu, T);

    for (int i=0; i<101; i++) {
        double z = i; 
        fprintf(fPtr, "%f, %f \n", z/101, nextArr[i]);
    }

    fclose(fPtr);
}

void LW(double *initialCondArr, int T, double mu, FILE *fPtr, int caseNo) {
    double nextArr[101];

    fPtr = fopen("file.csv", "w");

    for (int t=0; t<T; t++) {
        for(int i=1; i<100; i++) {
            nextArr[i] = initialCondArr[i] - (mu / 2) * (initialCondArr[i + 1] - initialCondArr[i - 1]) + (mu * mu / 2) * (initialCondArr[i + 1] - 2*initialCondArr[i] + initialCondArr[i - 1]);
        }
        for (int h=1; h<100; h++) {
            initialCondArr[h] = nextArr[h];
        }

        initialCondArr[0] = 0;
        initialCondArr[100] = nextArr[99];
        nextArr[0] = 0;
        nextArr[100] = nextArr[99];
    }

    fprintf(fPtr, "LW - %d - %.2f @ T = %d \n ", caseNo, mu, T);

    for (int i=0; i<101; i++) {
        double z = i; 
        fprintf(fPtr, "%f, %f \n", z/101, nextArr[i]);
    }

    fclose(fPtr);
}

void BW(double *initialCondArr, int T, double mu, FILE *fPtr, int caseNo) {
    double nextArr[101];

    fPtr = fopen("file.csv", "w");

    for (int t=0; t<T; t++) {
        
        for(int i=2; i<101; i++) {
            nextArr[i] = initialCondArr[i] - (mu / 2) * (3*initialCondArr[i] - 4*initialCondArr[i - 1] + initialCondArr[i - 2]) + (mu * mu / 2) * (initialCondArr[i] - 2*initialCondArr[i - 1] + initialCondArr[i - 2]);
        }

        for (int h=2; h<101; h++) {
            initialCondArr[h] = nextArr[h];
        }

        initialCondArr[0] = 0;
        initialCondArr[1] = 0;
        nextArr[0] = 0;
        nextArr[1] = 0;
    }

    fprintf(fPtr, "BW - %d - %.2f @ T = %d \n ", caseNo, mu, T);

    for (int i=0; i<101; i++) {
        double z = i; 
        fprintf(fPtr, "%f, %f \n", z/101, nextArr[i]);
    }

    fclose(fPtr);
}

void FR(double *initialCondArr, int T, double mu, FILE *fPtr, int caseNo) {
    double nextArrBW[101];
    double nextArrLW[101];
    double nextArr[101];

    fPtr = fopen("file.csv", "w");

    for (int t=0; t<T; t++) {
        for(int i=2; i<100; i++) {
            nextArrBW[i] = initialCondArr[i] - (mu / 2) * (3*initialCondArr[i] - 4*initialCondArr[i - 1] + initialCondArr[i - 2]) + (mu * mu / 2) * (initialCondArr[i] - 2*initialCondArr[i - 1] + initialCondArr[i - 2]);
            nextArrLW[i] = initialCondArr[i] - (mu / 2) * (initialCondArr[i + 1] - initialCondArr[i - 1]) + (mu * mu / 2) * (initialCondArr[i + 1] - 2*initialCondArr[i] + initialCondArr[i - 1]);
        }

        nextArrLW[1] = initialCondArr[1] - (mu / 2) * (initialCondArr[2] - initialCondArr[0]) + (mu * mu / 2) * (initialCondArr[2] - 2 * initialCondArr[1] + initialCondArr[0]);
        nextArrBW[100] = initialCondArr[100] - (mu / 2) * (3 * initialCondArr[100] - 4 * initialCondArr[99] + initialCondArr[98]) + (mu * mu / 2) * (initialCondArr[100] - 2 * initialCondArr[99] + initialCondArr[98]);

        for (int h=1; h<101; h++) {
            nextArr[h] = 0.5 * (nextArrBW[h] + nextArrLW[h]);
            initialCondArr[h] = nextArr[h];
        }

        initialCondArr[0] = 0;
        nextArr[0] = 0;
    }

    fprintf(fPtr, "FR - %d - %.2f @ T = %d \n ", caseNo, mu, T);

    for (int i=0; i<101; i++) {
        double z = i; 
        fprintf(fPtr, "%f, %f \n", z/101, nextArr[i]);
    }

    fclose(fPtr);
}

void FTFSComplete(double *initialCondArr, double mu, FILE *fPtr, int caseNo) {
    double nextArr[101];
    double complete[100][101];

    fPtr = fopen("file.csv", "w");

    for (int t = 0; t < 100; t++) {
        for (int i = 0; i < 100; i++) {
            nextArr[i] = initialCondArr[i] - mu * (initialCondArr[i + 1] - initialCondArr[i]);
        }
        for (int h = 0; h < 100; h++) {
            initialCondArr[h] = nextArr[h];
        }
        initialCondArr[100] = nextArr[99];
        nextArr[100] = nextArr[99];

        for (int i=0; i<101; i++) {
            complete[t][i] = nextArr[i];
        }
    }

    fprintf(fPtr, "FTFS - %d - %.2f \n", caseNo, mu);

    for (int t=0; t<100; t++) {
        for (int i=0; i<101; i++) {
            fprintf(fPtr, "%f,", complete[t][i]);
        }
        fprintf(fPtr, "\n");
    }

    fclose(fPtr);
}

void FTCSComplete(double *initialCondArr, double mu, FILE *fPtr, int caseNo) {
    double nextArr[101];
    double complete[100][101];

    fPtr = fopen("file.csv", "w");

    for (int t = 0; t < 100; t++) {
        for (int i = 1; i < 100; i++) {
            nextArr[i] = initialCondArr[i] - (mu/2)*(initialCondArr[i+1] - initialCondArr[i-1]);
        }
        for (int h = 1; h < 100; h++) {
            initialCondArr[h] = nextArr[h];
        }
        initialCondArr[0] = 0;
        initialCondArr[100] = nextArr[99];
        nextArr[0] = 0;
        nextArr[100] = nextArr[99];

        for (int i=0; i<101; i++) {
            complete[t][i] = nextArr[i];
        }
    }

    fprintf(fPtr, "FTCS - %d - %.2f \n ", caseNo, mu);

    for (int t=0; t<100; t++) {
        for (int i=0; i<101; i++) {
            fprintf(fPtr, "%f,", complete[t][i]);
        }
        fprintf(fPtr, "\n");
    }

    fclose(fPtr);
}

void FTBSComplete(double *initialCondArr, double mu, FILE *fPtr, int caseNo) {
    double nextArr[101];
    double complete[100][101];

    fPtr = fopen("file.csv", "w");

    for (int t = 0; t < 100; t++) {
        for (int i = 1; i < 101; i++) {
            nextArr[i] = initialCondArr[i] - mu*(initialCondArr[i] - initialCondArr[i-1]);
        }
        for (int h = 1; h < 101; h++) {
            initialCondArr[h] = nextArr[h];
        }
        nextArr[0] = nextArr[1];
        initialCondArr[0] = 0;

        for (int i=0; i<101; i++) {
            complete[t][i] = nextArr[i];
        }
    }

    fprintf(fPtr, "FTBS - %d - %.2f \n ", caseNo, mu);

    for (int t=0; t<100; t++) {
        for (int i=0; i<101; i++) {
            fprintf(fPtr, "%f,", complete[t][i]);
        }
        fprintf(fPtr, "\n");
    }

    fclose(fPtr);
}

void LWComplete(double *initialCondArr, double mu, FILE *fPtr, int caseNo) {
    double nextArr[101];
    double complete[100][101];

    fPtr = fopen("file.csv", "w");

    for (int t = 0; t < 100; t++) {
        for (int i = 1; i < 100; i++) {
            nextArr[i] = initialCondArr[i] - (mu / 2) * (initialCondArr[i + 1] - initialCondArr[i - 1]) + (mu * mu / 2) * (initialCondArr[i + 1] - 2 * initialCondArr[i] + initialCondArr[i - 1]);
        }
        for (int h = 1; h < 100; h++) {
            initialCondArr[h] = nextArr[h];
        }

        initialCondArr[0] = 0;
        initialCondArr[100] = nextArr[99];
        nextArr[0] = 0;
        nextArr[100] = nextArr[99];

        for (int i=0; i<101; i++) {
            complete[t][i] = nextArr[i];
        }
    }

    fprintf(fPtr, "LW - %d - %.2f \n ", caseNo, mu);

    for (int t=0; t<100; t++) {
        for (int i=0; i<101; i++) {
            fprintf(fPtr, "%f,", complete[t][i]);
        }
        fprintf(fPtr, "\n");
    }

    fclose(fPtr);
}

void BWComplete(double *initialCondArr, double mu, FILE *fPtr, int caseNo) {
    double nextArr[101];
    double complete[100][101];

    fPtr = fopen("file.csv", "w");

    for (int t = 0; t < 100; t++) {

        for (int i = 2; i < 101; i++) { 
            nextArr[i] = initialCondArr[i] - (mu / 2) * (3 * initialCondArr[i] - 4 * initialCondArr[i - 1] + initialCondArr[i - 2]) + (mu * mu / 2) * (initialCondArr[i] - 2 * initialCondArr[i - 1] + initialCondArr[i - 2]);
        }

        for (int h = 2; h < 101; h++) {
            initialCondArr[h] = nextArr[h];
        }

        initialCondArr[0] = 0;
        initialCondArr[1] = 0;
        nextArr[0] = 0;
        nextArr[1] = 0;

        for (int i=0; i<101; i++) {
            complete[t][i] = nextArr[i];
        }
    }

    fprintf(fPtr, "BW - %d - %.2f \n ", caseNo, mu);

    for (int t=0; t<100; t++) {
        for (int i=0; i<101; i++) {
            fprintf(fPtr, "%f,", complete[t][i]);
        }
        fprintf(fPtr, "\n");
    }

    fclose(fPtr);
}

void FRComplete(double *initialCondArr, double mu, FILE *fPtr, int caseNo) {
    double nextArrBW[101];
    double nextArrLW[101];
    double nextArr[101];
    double complete[100][101];

    fPtr = fopen("file.csv", "w");

    for (int t=0; t<100; t++) {
        for(int i=2; i<100; i++) {
            nextArrBW[i] = initialCondArr[i] - (mu / 2) * (3*initialCondArr[i] - 4*initialCondArr[i - 1] + initialCondArr[i - 2]) + (mu * mu / 2) * (initialCondArr[i] - 2*initialCondArr[i - 1] + initialCondArr[i - 2]);
            nextArrLW[i] = initialCondArr[i] - (mu / 2) * (initialCondArr[i + 1] - initialCondArr[i - 1]) + (mu * mu / 2) * (initialCondArr[i + 1] - 2*initialCondArr[i] + initialCondArr[i - 1]);
        }

        nextArrLW[1] = initialCondArr[1] - (mu / 2) * (initialCondArr[2] - initialCondArr[0]) + (mu * mu / 2) * (initialCondArr[2] - 2 * initialCondArr[1] + initialCondArr[0]);
        nextArrBW[100] = initialCondArr[100] - (mu / 2) * (3 * initialCondArr[100] - 4 * initialCondArr[99] + initialCondArr[98]) + (mu * mu / 2) * (initialCondArr[100] - 2 * initialCondArr[99] + initialCondArr[98]);

        for (int h=1; h<101; h++) {
            nextArr[h] = 0.5 * (nextArrBW[h] + nextArrLW[h]);
            initialCondArr[h] = nextArr[h];
        }

        initialCondArr[0] = 0;
        nextArr[0] = 0;

        for (int i=0; i<101; i++) {
            complete[t][i] = nextArr[i];
        }
    }

    fprintf(fPtr, "FR - %d - %.2f \n ", caseNo, mu);

    for (int t=0; t<100; t++) {
        for (int i=0; i<101; i++) {
            fprintf(fPtr, "%f,", complete[t][i]);
        }
        fprintf(fPtr, "\n");
    }

    fclose(fPtr);
}

int main(int argc, char *argv[]) {

    FILE * fPtr;
    double initialCondArr[101];
    int caseNo = atoi(argv[1]);
    int muSelector = atoi(argv[2]);
    int method = atoi(argv[3]);
    double mu;
    bool valid = true;
    char cont;

    // printf("Please select initial conditions from following options: \n 1. Case-1 \n 2. Case-2 \n 3. Case-3 \n 4. Case-4\n");
    // scanf("%d", &caseNo);

    switch(caseNo) {
        case 1: 
            case1(initialCondArr);
            break;
        case 2: 
            case2(initialCondArr);
            break;
        case 3: 
            case3(initialCondArr);
            break;
        case 4: 
            case4(initialCondArr);
            break;
        default:
            printf("Sorry, Invalid!");
            valid = false;
            break;
    }

    // printf("Select mu: \n 1. 0.5 \n 2. 1.0 \n 3. 1.5\n");
    // scanf("%d",&muSelector);

    switch(muSelector) {
        case 1: 
            mu = 0.5;
            break;
        case 2: 
            mu = 1.0;
            break;
        case 3: 
            mu = 1.5;
            break;
        default:
            printf("Sorry, Invalid!");
            valid = false;
            break;
    }

    // printf("Select a Method: \n 1. FTFS \n 2. FTCS \n 3. FTBS \n 4. LW \n 5. BW \n 6. FR\n");
    // scanf("%d", &method);

    switch(method) {
        case 1: 
            // FTFS(initialCondArr, 40, mu, fPtr, caseNo);
            FTFSComplete(initialCondArr, mu, fPtr, caseNo);
            break;
        case 2:
            // FTCS(initialCondArr, 40, mu, fPtr, caseNo);
            FTCSComplete(initialCondArr, mu, fPtr, caseNo);
            break;
        case 3:
            // FTBS(initialCondArr, 40, mu, fPtr, caseNo);
            FTBSComplete(initialCondArr, mu, fPtr, caseNo);
            break;
        case 4:
            // LW(initialCondArr, 40, mu, fPtr, caseNo);
            LWComplete(initialCondArr, mu, fPtr, caseNo);
            break;
        case 5:
            // BW(initialCondArr, 40, mu, fPtr, caseNo);
            BWComplete(initialCondArr, mu, fPtr, caseNo);
            break;
        case 6:
            // FR(initialCondArr, 40, mu, fPtr, caseNo);
            FRComplete(initialCondArr, mu, fPtr, caseNo);
            break;
        default:
            printf("Sorry, Invalid!");
            valid = false;
            break;
    }

    // printf("File saved in working directory\n");
    // scanf(" %c", &cont);

    // if (cont == 'n') {
    //     valid = false;
    //     break;
    // }

    return 0;
}