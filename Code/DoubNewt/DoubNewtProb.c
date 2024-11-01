#include <stdio.h>
#include <math.h>

//----------------------INTERFACE-------------------------
#define TOLERANCE 1e-6
#define MAX_ITER 100

// Function to calculate f1 and f2
void f(double x1, double x2, double *f1, double *f2) 
{
    *f1 = pow(x1, 2) + pow(x2, 2) - 1;
    *f2 = 5* pow(x1, 2) - x2 - 2;
}
//Consolidated
//----------------------------------------------------------

// Function to calculate Jacobian
void jacobian(double x1, double x2, double J[2][2])
{
    J[0][0] = 2*x1;
    J[0][1] = 2*x2;
    J[1][0] = 10*x1;
    J[1][1] = -1;
}

// Function to solve linear equations using Cramers rule(not the seinfeld one)
void CramerCramer(double A[2][2], double b[2], double dx[2]) 
{
    double det = A[0][0]*A[1][1] - A[0][1]*A[1][0];
    if (fabs(det) > TOLERANCE) {
        dx[0] = (b[0]*A[1][1] - b[1]*A[0][1]) / det;
        dx[1] = (A[0][0]*b[1] - A[1][0]*b[0]) / det;
    } else {
        printf("Jacobian singular, cannot proceed.\n");
        dx[0] = dx[1] = 0;
    }
}

// Newton's method
void duke_newton2(double *x1, double *x2, double x1_init, double x2_init) 
{
    double x[2] = {x1_init, x2_init};
    double f1, f2, J[2][2], dx[2];
    int iter = 0;

    do {
        f(x[0], x[1], &f1, &f2);
        jacobian(x[0], x[1], J);
        
        double F[2] = {-f1, -f2};
        CramerCramer(J, F, dx);
        
        x[0] += dx[0];
        x[1] += dx[1];

        iter++;
        if (iter > MAX_ITER) {
            printf("Max iterations reached.\n");
            break;
        }
    } while (fabs(f1) > TOLERANCE || fabs(f2) > TOLERANCE);

    *x1 = x[0];
    *x2 = x[1];
}

int main() 
{
    double x1, x2;
    
    // Initial guesses, I cheated and used a graph to pick out places closish to the intersections(but not too close)
    double initial_guesses[][2] = {
        {0.9, 0.5},  
        {-0.9, 0.5}, 
        {-0.5, -1.5},
        {0.5, -1.5} 
    };

    for (int i = 0; i < 4; i++) {
        duke_newton2(&x1, &x2, initial_guesses[i][0], initial_guesses[i][1]);
        printf("Solution %d: x1 = %f, x2 = %f\n", i+1, x1, x2);
    }

    return 0;
}
