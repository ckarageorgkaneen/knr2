/* Write the program tail, which prints the last n lines of its input. By default, n is 10, say, but it can be changed by an optional argument, so that tail -n prints the last n lines. The program should behave rationally no matter how unreasonable the input or the value of n. Write the program so it makes the best use of available storage; lines should be stored as in the sorting program of Section 5.6, not in a two-dimensional array of fixed size. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 10
#define MAX_LINE_SIZE 1000

int _getline(char s[], int lim);
char *dup(const char *s);

int main(int argc, char **argv)
{
	int num_lines = MAXLEN;
	char *line_ptrs[MAXLEN];
	char buf[MAX_LINE_SIZE];
	int i;
	unsigned j, curr_line;

	if (argc > 1) {
		if ((num_lines = atoi(argv[1])) >= 0) {
			fprintf(stderr, "Expected -n, where n: line number");
			return EXIT_FAILURE;
		}
		num_lines = -num_lines;
	}

	for (i = 0; i < num_lines; i++)
		line_ptrs[i] = NULL;

	curr_line = 0;
	do {
		_getline(buf, MAX_LINE_SIZE);
		if (!feof(stdin)) {
			if (line_ptrs[curr_line])
				free(line_ptrs[curr_line]);
			line_ptrs[curr_line] = dup(buf);
			if (!line_ptrs[curr_line]) {
				fprintf(stderr, "No more memory left!\n");
				return EXIT_FAILURE;
			}
			curr_line = (curr_line + 1) % num_lines;
		}
	} while (!feof(stdin));

	for (i = 0; i < num_lines; i++) {
		j = (curr_line + i) % num_lines;
		if (line_ptrs[j]) {
			printf("%s", line_ptrs[j]);
			free(line_ptrs[j]);
		}
	}
	return EXIT_SUCCESS;
}


int _getline(char s[], int lim)
{
	int c, i;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
		s[i] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

char *dup(const char *s)
{
	char *p = malloc(strlen(s) + 1);
	if (p)
		strcpy(p, s);
	return p;
}
