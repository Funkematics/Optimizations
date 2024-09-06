#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <stdbool.h>

#define MIN 0.0
#define MAX 2.0
#define STEP 0.000005
#define EPSILON 1e-6

double f(double x)
{
    return pow((pow(x, 2) + sin(x)), 2) - 10 * (cos(5 * x) + (3.0/2.0) * x);
}
//derivative using central finite differences
double deriv(double x, double h)
{
    return (f(x+h) - f(x-h)) / (2.0*h);
}
//second order deriv using central finite differences
long double secderiv(double x, double h)
{
    return (f(x+h) - 2*f(x) + f(x-h)) / (h * h);
}

bool signCheck(double prev, double curr)
{
    // Check if the sign has changed, considering EPSILON for near-zero values
    if ((prev > EPSILON && curr < -EPSILON) || (prev < -EPSILON && curr > EPSILON)) {
        return true;
    }
    return false;
}

double duke_newton(double x0, double h, double tolerance, int max_iterations)
{
  double x = x0;
  double x_new;

  for (int i = 0; i < max_iterations; i++){
    x_new = x - deriv(x, h) / secderiv(x, h);

    if (fabs(x_new - x) < tolerance) {
      return x_new;
    }
    x = x_new;
  }
  printf("Did not converge within %d iterations for given range.\n", max_iterations);
  return x_new;
}

int main()
{
    double h = 1e-6;
    double x;
    int inflections = 1;  //We set it to 1 because we are expecting continuous functions
                     // non linear function
    double prev_deriv = secderiv(MIN, h); // Start with the first value

    for (x = MIN; x <= MAX; x += STEP) {
        double curr_deriv = secderiv(x, h);
        if (signCheck(prev_deriv, curr_deriv)) {
            ++inflections;
            printf("point : %f\n", x);
        }
        prev_deriv = curr_deriv;
        //printf("second deriv x = %f, f(x)'' = %Lf\n", x, secderivrx, h));
    }
    double guesses[inflections];
    printf("curves : %d\n", inflections);
    printf("root 1: %f\n", duke_newton(1.255, h, EPSILON, 6));
    return 0;
}
