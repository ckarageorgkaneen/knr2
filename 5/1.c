/* As written, getint treats a + or - not followed by a digit as a valid representation of zero. Fix it to push such a character back on the input. */
#include <ctype.h>
#include <stdio.h> /* for EOF */
#include <assert.h>

#define BUFSIZE 10

int getch(void);
void ungetch(int);
int getint(int *);

int main()
{
	int n;
	assert(getint(&n));
}

int getint(int *pn)
{
	int c, sign, sawsign;

	while (isspace(c = getch()))
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c);
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (sawsign = (c == '+' || c == '-'))
		c = getch();
	if (!isdigit(c)) {
		ungetch(c);
		if (sawsign)
			ungetch((sign == -1) ? '-' : '+');
		return 0;
	}
	for (*pn = 0; isdigit(c); c = getch())
		* pn = 10 * *pn + (c - '0');
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}

int bufp = 0;
int buf[BUFSIZE];

int getch(void)
{
	return bufp > 0 ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp < BUFSIZE)
		buf[bufp++] = c;
}
