/* Write the function strrindex(s,t) , which returns the position of the rightmost occurrence of t in s , or -1 if there is none. */
#include <stdio.h>
#include <assert.h>

int strrindex(char s[], char t);

int main()
{
	assert(strrindex("s is surely the char you're looking for!", 's') == 5);
}

int strrindex(char s[], char t)
{
	int count = -1;
	for (int i = 0; s[i] != '\0'; i++)
		if (s[i] == t)
			count = i;
	return count;
}


