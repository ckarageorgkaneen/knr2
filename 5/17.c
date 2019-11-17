/* Add a field-handling capability, so sorting may be done on fields within lines, each field sorted according to an independent set of options. (The index for this book was sorted with -df for the index category and -n for the page numbers.) */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0

#define MAXLINES 5000       /* maximum number of lines */
#define MAXLEN 1000         /* maximum length of a line */
#define MAXSTR 100

char *lineptr[MAXLINES];
int reverse = FALSE;
int numeric = FALSE;
int fold = FALSE;
int dir = FALSE;

void readargs(int argc, char ** argv);
int _getline(char s[], int lim);
int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);
int numcmp(const void *p1, const void *p2);
int charcmp(const void *p1, const void *p2);
void substr(char *s, char *str);


int pos1 = 0;
int pos2 = 0;

int main(int argc, char **argv)
{
	int nlines;

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		qsort(lineptr, nlines, sizeof * lineptr, numeric ? numcmp : charcmp);
		writelines(lineptr, nlines);
		return EXIT_SUCCESS;
	}
	else {
		fputs("input too big for sorting!\n", stderr);
		return EXIT_FAILURE;
	}
}

void readargs(int argc, char **argv)
{
	for (int i = 1; i < argc && (*argv[i] == '-' || *argv[i] == '+'); i++) {
		if (*argv[i] == '-' && !isdigit(*(argv[i] + 1))) {
			switch (*(argv[i] + 1)) {
			case 'n':
				numeric = TRUE;
				break;
			case 'r':
				reverse = TRUE;
				break;
			case 'f':
				fold = TRUE;
				break;
			case 'd':
				dir = TRUE;
				break;
			default:
				fprintf(stderr, "invalid flag '%s'", argv[i]);
				fprintf(stderr, "Usage: sort -dfnr [+pos1] [-pos2]");
				exit(EXIT_FAILURE);
			}
		}
		else if (*argv[i] == '-')
			pos2 = atoi(argv[i] + 1);
		else if ((pos1 = atoi(argv[i] + 1) < 0)) {
			fprintf(stderr, "Usage: sort -dfnr [+pos1] [-pos2]");
			exit(EXIT_FAILURE);
		}
	}
	if (pos1 > pos2) {
		fprintf(stderr, "Usage: sort -dfnr [+pos1] [-pos2]");
		exit(EXIT_FAILURE);
	}
}

int _getline(char s[], int lim)
{
	int c, i;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
		s[i] = c;
	if (c == '\n') {
		s[i++] = c;
	}
	s[i] = '\0';
	return i;
}

int readlines(char *lineptr[], int maxlines)
{
	int len, nlines;
	char *p, line[MAXLEN];

	nlines = 0;
	while ((len = _getline(line, MAXLEN)) > 0)
		if (nlines >= maxlines || (p = malloc(len)) == NULL)
			return -1;
		else {
			line[len - 1] = '\0';  /* delete the newline */
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	return nlines;
}

void writelines(char *lineptr[], int nlines)
{
	for (int i = 0; i < nlines; i++)
		printf("%s\n", lineptr[i]);
}

int charcmp(const void *p1, const void *p2)
{
	char **s1 = (char **)p1;
	char **s2 = (char **)p2;
	char a, b;
	int i, j, endpos;

	i = j = pos1;
	if (pos2 > 0)
		endpos = pos2;
	else if ((endpos = strlen(*s1)) > strlen(*s2))
		endpos = strlen(*s2);

	do {
		if (dir) {
			for (; i < endpos && !isalnum((*s1)[i]) &&
			        (*s1)[i] != ' ' && (*s1)[i] != '\0'; i++)
				;
			for (; j < endpos && !isalnum((*s2)[j]) &&
			        (*s2)[j] != ' ' && (*s2)[j] != '\0'; j++)
				;
		}
		if (i < endpos && j < endpos) {
			a = fold ? toupper((*s1)[i]) : (*s1)[i];
			i++;
			b = fold ? toupper((*s2)[j]) : (*s2)[j];
			j++;
			if (a == b && a == '\0')
				return 0;
		}
	} while (a == b && i < endpos && j < endpos);

	return a - b;
}

int numcmp(const void *p1, const void *p2)
{
	char * const *s1 = reverse ? p2 : p1;
	char * const *s2 = reverse ? p1 : p2;
	double v1, v2;
	char str[MAXSTR];

	substr(*s1, str);
	v1 = atof(*s1);
	substr(*s2, str);
	v2 = atof(*s2);
	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

void substr(char *s, char *str)
{
	int i, j, slen;

	slen = strlen(s);
	if (pos2 > 0 && slen > pos2)
		slen = pos2;
	else if (pos2 > 0 && slen < pos2) {
		fprintf(stderr, "substr: input string is too short");
		exit(EXIT_FAILURE);
	}
	for (i = pos1, j = 0; i < slen; i++, j++)
		str[j] = s[i];
	str[j] = '\0';
}
