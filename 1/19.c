/* Write a function reverse(s) that reverses the character string s . Use it to write a program that reverses its input a line at a time. */
#include <stdio.h>

#define MAX_LINE 1024

void discardnewline(char *s)
{
	while (*s != '\0') {
		if (*s == '\n')
			*s = '\0';
		++s;
	}
}

void reverse(char *s)
{
	char c;
	int i, j;

	for (j = 0; s[j] != '\0'; j++) {}

	--j;

	for (i = 0; i < j; i++) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
		--j;
	}
}

int getline(char *s, int lim)
{
	int c, i;
	for (i = 0; (i < lim - 1) && ((c = getchar()) != EOF) && (c != '\n'); i++)
		s[i] = c;

	if (c == '\n')
		s[i++] = c;

	s[i] = '\0';

	return i;
}

int main(void)
{
	char line[MAX_LINE];

	while (getline(line, sizeof line) > 0) {
		discardnewline(line);
		reverse(line);
		printf("%s\n", line);
	}

	return 0;
}
