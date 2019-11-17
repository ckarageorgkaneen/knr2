/* Modify the temperature conversion program to print the table in reverse order, that is, from 300 degrees to 0. */
#include <stdio.h>

int main(void)
{
  float fahr, celsius;
  int lower, upper, step;

  lower = 0;
  upper = 300;
  step = 20;

  printf("C     F\n\n");
  celsius = upper;
  while (celsius >= lower)
  {
    fahr = (9.0 / 5.0) * celsius + 32.0;
    printf("%3.0f %6.1f\n", celsius, fahr);
    celsius = celsius - step;
  }
  return 0;
}