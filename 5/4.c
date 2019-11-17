/* Write the function strend(s,t) , which returns 1 if the string t occurs at the end of the string s , and zero otherwise. */
#include <stdio.h>
#include <string.h>
#include <assert.h>

int strend(char *s, char *t);

int main()
{
	char *s = "blue is my favorite color";
	char *t = "color";
	assert(strend(s, t));
	t = "colour";
	assert(!strend(s, t));
}

int strend(char *s, char *t)
{
	s += (strlen(s) - strlen(t));
	while (*s++ == *t++)
		if (*s == '\0')
			return 1;
	return 0;
}
