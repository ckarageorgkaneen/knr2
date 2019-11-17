/*  Write a program to count blanks, tabs, and newlines. */
#include <stdio.h>

int main()
{
	int c = 0, ns, nt, nl;
	ns = nt = nl = 0;
	while ((c = getchar()) != EOF)
	{
		if (c == ' ') ns++;
		if (c == '\t') nt++;
		if (c == '\n') nl++;
	}
	printf("ns:%d\nnt:%d\nnl:%d", ns, nt, nl);
}
