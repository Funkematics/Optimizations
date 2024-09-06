#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <stdbool.h>

//200,000 points as recommended
#define MIN 0.0
#define MAX 2.0
#define STEP 0.000005
#define EPSILON 1e-6


struct feasibles {
  double* xval;
  uint32_t size;
};

struct extrema {
  double* xval;
  uint32_t size;
};

double f(double x)
{
  return pow((pow(x, 2) + sin(x)), 2) - 10 * (cos( 5 * x) + (3.0/2.0) * x);
}

double deriv(double x, double h)
{
  return (f(x+h) - (f(x-h))) / (2.0*h);
}

long double secderiv(double x, double h)
{
  return (f(x+h) - 2*(f(x)) + f(x-h)) / pow(h, 2);
}

bool signCheck(double y1)
{
  double y2 = y1 + STEP;

  if ((y2 > 0 && y1 < 0) || (y2 < 0 && y1 > 0)){
    return true;
  }
  return false;
}

int main()
{
  double h = 1e-5;
  double x;
  int signflips = 0;
  for (x = MIN; x <= MAX; x+= STEP){
    double derivout = deriv(x, h);
    double secderivout = secderiv(x, h);
    //printf("signchecks : %b \n", signCheck(secderivout));
    if (signCheck(secderivout) == true) {
      ++signflips;
    }
  //  printf(" Critical Point found at x = %f, f(x) = %f\n", x, f(x));
    printf("second deriv x = %f, f(x)'' = %Lf\n", x, secderiv(x, h));
  }
 // printf("y = %Lf\n", f(5.0));
 //printf("deriv = %.30Lf\n", deriv(1.2598, 1e-5));
   printf("sign flips : %d\n", signflips);
  return 0;
}
