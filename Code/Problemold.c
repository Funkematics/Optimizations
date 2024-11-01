#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <stdbool.h>

//----------------------INTERFACE-------------------------
#define MIN -10.0
#define MAX 10.0
#define STEP 0.05
#define EPSILON 1e-6
#define STORAGE 100

double f(double x)
{
    return pow(x, 3) - 5 * pow(x, 2) - 12 * x + 19;
}
//----------------------------------------------------------
//The above block is where we determine our range in MIN and MAX, our epsilon, steps,
//max storage size for extrema, this will be replaced with a dynamic memory, and finally
//our input function

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

//Newtons Method for finding critical points
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
    double h = EPSILON; //Just for notational convenience
    double x;
    int inflectionscount = 1;  // This is more of a count of convexities or concavity.

    int i = 0;         //index
    double inflections[STORAGE];
    inflections[i] = MIN;
    ++i;

    // Here we find inflections/concavities/convexities and put our data in an array.
    double prev_deriv = secderiv(MIN, h);       // Start with the first value
    for (x = MIN; x <= MAX; x += STEP) {        
        double curr_deriv = secderiv(x, h);
        if (signCheck(prev_deriv, curr_deriv)) { 
            ++inflectionscount;
            inflections[i] = x;
            i++;
            //printf("point : %f\n", x);
        }
        prev_deriv = curr_deriv;
        //printf("second deriv x = %f, f(x)'' = %Lf\n", x, secderivrx, h));
    }
    inflections[i]  = MAX;

    double guess;
    double out;
    for(i = 0; i <= inflectionscount; i++) {
      guess = (inflections[i] + inflections[i-1]) / 2;
     // printf("output : %f\n", out); 
      if(i != 0) {
        out = duke_newton(guess, h, EPSILON, 6);
        printf("feasible x: %.5f        y: %.5f\n" , out, f(out));
      }
    }
      

    printf("curves : %d\n", inflectionscount);
    return 0;
}
