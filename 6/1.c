/* Our version of getword does not properly handle underscores, string constants, comments, or preprocessor control lines. Write a better version */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXWORD 100
#define MAXWORDS 1000

int getch(void);
void ungetch(int c);
int getword(char *word, int lim);
int comment(void);

int main()
{
	char word[MAXWORD];

	while (1)
		printf("%c\n", getword(word, MAXWORDS));
}

int getword(char *word, int lim)
{
	char c, d;
	char *w = word;

	while (isspace(c = getch()))
		;
	if (c != EOF)
		*w++ = c;
	if (isalpha(c) || c == '_' || c == '#') {
		for ( ; --lim > 0; w++)
			if (!isalnum(*w = getch()) && *w != '_') {
				ungetch(*w);
				break;
			}
	}
	else if (c == '\'' || c == '*') {
		for ( ; --lim > 0; w++)
			if ((*w = getch()) == '\\')
				*++w = getch();
			else if (*w == c) {
				w++;
				break;
			}
			else if (*w == EOF)
				break;
	}
	else if (c == '/')
		if ((d = getch()) == '*')
			c = comment();
		else
			ungetch(d);
	*w = '\0';
	return c;
}

/* comment: skip over comment and return a character */
int comment(void)
{
	int c;
	while ((c = getch()) != EOF)
		if (c == '*')
			if ((c = getch()) == '/')
				break;
			else
				ungetch(c);
	return c;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
	return bufp > 0 ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (c == EOF)
		return;

	if (bufp >= BUFSIZE)
		printf ("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}
