/* Write a program detab that replaces tabs in the input with the proper number of blanks to space to the next tab stop. Assume a fixed set of tab stops, say every n columns. Should n be a variable or a symbolic parameter? */
#include <stdio.h>

#define TABSIZE 5

int main(void)
{
	int c, col_pos, spaces;
	col_pos = 0;

	while ((c = getchar()) != EOF) {
		if (c == '\n') {
			putchar(c);
			col_pos = 0;
		}
		else if (c == '\t') {
			spaces = TABSIZE - col_pos % TABSIZE;
			while (spaces-- != 0) {
				putchar(' ');
				col_pos++;
			}
		}
		else {
			putchar(c);
			col_pos++;
		}
	}
	return 0;
}
