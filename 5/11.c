/* Modify the programs entab and detab (written as exercises in Chapter 1) to accept a list of tab stops as arguments. Use the default tab settings if there are no arguments. */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define STRSIZE 5000

void entab(char *s, int tabsize);
void detab(char *s, int tabsize);
int _getline(char *s, int lim);

int main(int argc, char *argv[])
{
	int tablen = 8;
	char s[STRSIZE];

	if (argc > 1) {
		if (isdigit((*++argv)[0]))
			tablen = atoi(argv[0]);
		else
			printf("error: invalid params");
	}

	printf("tablen: %d\n\n", tablen);

	while (_getline(s, STRSIZE) > 0) {
		detab(s, tablen);
		printf("%s", s);
	}

}

void entab(char *s, int tabsize)
{
	char *s_start = s;
	char *det = s;

	while (*s++ = *det++) {
		if ((s - s_start) % tabsize == 0 && *s == ' ') {
			while (*det-- == ' ')
				;
			*det = '\t';
		}
	}
}

void detab(char *s, int tabsize)
{
	char *s_start = s;
	char s_copy[STRSIZE];
	char *cp = &s_copy[0];

	while (*cp++ = *s++) {
		while (*s == '\t') {
			do {
				*cp++ = ' ';
			} while ((cp - &s_copy[0]) % tabsize != 0);
			s++;
		}
	}

	s = s_start;
	cp = &s_copy[0];
	while (*s++ = *cp++)
		;
	s = s_start;
}

int _getline(char *s, int lim)
{
	if (lim < 0)
		return -1;

	char *p;
	int c;

	p = s;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		* p++ = c;
	if (c == '\n')
		*p++ = c;
	*p = '\0';
	return (int)(p - s);
}
