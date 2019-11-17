/* Write getfloat , the floating-point analog of getint . What type does getfloat return as its function value? */
#include <ctype.h>
#include <stdio.h> /* for EOF */
#include <assert.h>
#include <math.h>

#define BUFSIZE 1000

int getch(void);
void ungetch(int);
int getfloat(float *);

int main()
{
	float f;
	assert(getfloat(&f));
}

int getfloat(float *pn)
{
	int c, sign;

	while (isspace(c = getch()));

	if (!isdigit(c) && c != EOF && c != '+' && c != '-')	{
		ungetch(c); //not a number
		return 0;
	}

	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-')
		c = getch();
	for (*pn = 0; isdigit(c); c = getch())
		* pn = 10 * *pn + (c - '0');
	if (c == '.')	{
		int i, dec;
		c = getch();
		for (i = 0; isdigit(c); c = getch(), i++)
			dec = 10 * dec + (c - '0');
		*pn += dec / (pow(10, i));
	}
	if (*pn == 0 && c != '0')	{ //if +/- is followed by NaN, pn will stay at 0
		ungetch(sign == 1 ? '+' : '-');
		return 0;
	}
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
