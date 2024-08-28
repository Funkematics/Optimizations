#include <stdio.h>
#include <math.h>

#define MIN 0.0
#define MAX 2.0
#define STEP 0.00000001
#define EPSILON 1e-6


long double f(long double x)
{
  return pow((pow(x, 2) + sin(x)), 2) - 10 * (cos( 5 * x) + (3.0/2.0) * x);
}

long double deriv(double x, double h)
{
  return (f(x+h) - (f(x-h))) / (2.0*h);
}

int main()
{
  long double h = 1e-5;
  double x;
  for (x = MIN; x <= MAX; x+= STEP){
    double derivout = deriv(x, h);
    if (fabs(derivout) < EPSILON){
      printf(" Critical Point found at x = %f, f(x) = %Lf\n", x, f(x));
    }
  }
  printf("y = %Lf\n", f(5.0));
  printf("deriv = %.30Lf\n", deriv(1.2598, 1e-5));
  return 0;
}
