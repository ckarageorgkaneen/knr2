/* Write a program that will print arbitrary input in a sensible way. As a minimum, it should print non-graphic characters in octal or hexadecimal according to local custom, and break long text lines. */
#include <stdio.h>
#include <ctype.h>

#define MAXLINE 100 /* max chars in line */
#define OCTLEN 6 /* length of an octal value*/

int inc(int pos, int n);

/* sensibly print arbitrary input */
int main()
{
	int c, pos;

	pos = 0;
	while ((c = getchar()) != EOF)
		if (iscntrl(c) || c == ' ') {
			/* non-graph or blank char */
			pos = inc(pos, OCTLEN);
			printf(" \\%03o", c);
			if (c == '\n') {
				pos = 0;
				putchar('\n');
			}
		} else {
			/* graphic char */
			pos = inc(pos, 1);
			putchar(c);
		}
	return 0;
}

/* inc: increment position counter for output */
int inc(int pos, int n)
{
	if (pos + n < MAXLINE)
		return pos + n;
	else {
		putchar('\n');
		return n;
	}
}
