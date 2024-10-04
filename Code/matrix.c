#include <stdio.h>

#define MAX_LENGTH 1000

struct 2dmat {
  double elem[][];
  int sizei;
  int sizej;

}

int main(void)
{
  FILE *matrix;
  char line[MAX_LENGTH];

  file = fopen("test.mat", "r");
  if (file == NULL) {
    perror("Error opening file");
    return -1'
}

