#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 1000

typedef struct mat {
  double **elem;
  int i;
  int j;

} mat;

mat* initMatrix(int rows, int cols)
{
  //For functions that operate on any matrix, we denote the matrix with capital letters internally
  //We use A, B, C .... Z etc, this is standard in many math texts.
  mat* A = (mat*)malloc(sizeof(mat));
  if (A == NULL) {
    fprintf(stderr, "Failure to allocate memory for matrix\n");
    return NULL;
  }

  A->i = rows;
  A->j = cols;

  A->elem = (double**)malloc(rows * sizeof(double*));
  if (A->elem == NULL) {
    fprintf(stderr, "Failure to allocate memory for elements in matrix\n");
    free(A);
    return NULL;
  }

  for (int i = 0; i < rows; i++) {
    A->elem[i] = (double*)malloc(cols * sizeof(int));
    if (A->elem[i] == NULL){
      fprintf(stderr, "Memory allocation failed\n");
      for (int j = 0; j < i; j++) {
        free(A->elem[j]);
      }
      free(A->elem);
      free(A);
      return NULL;
    }
  }
return A;
}

int main(void)
{
  return 0;
}
