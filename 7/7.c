/* Modify the pattern finding program of Chapter 5 to take its input from a set of named files or, if no files are named as arguments, from the standard input. Should the file name be printed when a matching line is found? */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 1000

void fpat(FILE *fp, char *fname, char *pattern,
          int except, int number);

/* find: print lines that match 1st arg pattern */
int main(int argc, char *argv[])
{
	char pattern[MAXLINE];
	int c, except = 0, number = 0;
	FILE *fp;

	while (--argc > 0 && (*++argv)[0] == '-')
		while (c = *++argv[0])
			switch (c) {
			case 'x':
				except = 1;
				break;
			case 'n':
				number = 1;
				break;
			default:
				printf("find: illegal option %c\n", c);
				argc = 0;
				break;
			}
	if (argc >= 1)
		strcpy(pattern, *argv);
	else {
		printf("Usage: find [-x] [-n] pattern [file ...]\n");
		exit(1);
	}

	if (argc == 1) /* read stdin */
		fpat(stdin, "", pattern, except, number);
	else
		while (--argc > 0) /* get a named file */
			if ((fp = fopen(*++argv, "r")) == NULL) {
				fprintf(stderr, "find: can't open %s\n", *argv);
				exit(1);
			} else {
				/* file has been opened */
				fpat(fp, *argv, pattern, except, number);
				fclose(fp);
			}
	return 0;
}

/* fpat: find pattern */
void fpat(FILE *fp, char *fname, char *pattern,
          int except, int number)
{
	char line[MAXLINE];
	long lineno = 0;

	while (fgets(line, MAXLINE, fp) != NULL) {
		++lineno;
		if ((strstr(line, pattern) != NULL) != except) {
			if (*fname) /* have a file name */
				printf("%s - ", fname);
			if (number) /* print line number */
				printf("%ld: ", lineno);
			printf("%s", line);
		}
	}
}

