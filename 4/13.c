/* Write a recursive version of the function reverse(s) , which reverses the string s in place. */
#include <stdio.h>
#include <string.h>
#include <assert.h>

void reverse(char s[]);

void main()
{
	char s[] = "Chris";
	reverse(s);
	assert(strcmp(s, "sirhC") == 0);
}

void reverse(char s[])
{
	static int i, j;

	if (s[i]) {
		int c = s[i++];
		reverse(s);
		s[j++] = c;
	}

	if (i == j)
		i = j = 0;
}
