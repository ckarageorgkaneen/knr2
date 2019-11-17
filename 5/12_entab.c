/* Extend entab and detab to accept the shorthand entab -m +n to mean tab stops every n columns, starting at column m. Choose convenient (for the user) default behavior. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABSIZE 8

int main(int argc, char **argv)
{
	int c, pos, spaces, i;
	int tabsize[2] = {TABSIZE, TABSIZE};

	while (--argc > 0 && (**++argv == '-' || **argv == '+'))
		switch (**argv) {
		case '-':
			if ((pos = atoi(*argv + 1)) > 0)
				tabsize[0] = pos;
			break;
		case '+':
			if ((pos = atoi(*argv + 1)) > 0)
				tabsize[1] = pos;
			break;
		}

	pos = spaces = i = 0;
	while ((c = getchar()) != EOF) {
		if (c == ' ') {
			if (pos < tabsize[i] - 1) {
				++pos;
				++spaces;
			}
			else {
				putchar('\t');
				pos = spaces = 0;
				if (i < 1)
					i++;
			}
		}
		else {
			if (c != '\t')
				while (spaces) {
					putchar(' ');
					spaces--;
				}

			putchar(c);

			if (c == '\n')
				pos = spaces = i = 0;
			else if (c == '\t') {
				pos = spaces = 0;
				if (i < 1)
					i++;
			}
			else {
				pos++;

				if (pos == tabsize[i]) {
					pos = 0;
					if (i < 1)
						i++;
				}
			}
		}
	}

	while (spaces) {
		putchar(' ');
		spaces--;
	}

	return 0;
}