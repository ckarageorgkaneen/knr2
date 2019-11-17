/* Rewrite the temperature conversion program of Section 1.2 to use a function for conversion. */
#include <stdio.h>

int fahr_celsius(int fahr);

int main(void)
{
	int i;

	for (i = 0; i <= 300; i = i + 20)
		printf("%d fahr %6d celsius \n", i, fahr_celsius(i));
	return 0;
}

int fahr_celsius(int t)
{
	return (5.0 / 9) * (t - 32);
}