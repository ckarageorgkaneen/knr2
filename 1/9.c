/* Write a program to copy its input to its output, replacing each string of one or more blanks by a single blank. */
#include <stdio.h>

int main()
{
	int c = EOF;
	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\t') {
			while ((c = getchar()) == ' ' || c == '\t');
			putchar(' ');
		}
		putchar(c);
	}
	return 0;
}

