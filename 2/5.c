/* Write the function any(s1,s2) , which returns the first location in the string s1 where any character from the string s2 occurs, or -1 if s1 contains no characters from s2 . (The standard library function strpbrk does the same job but returns a pointer to the location.) */
#include <stdio.h>
#include <assert.h>

int any(const char s1[], const char s2[]);

int main()
{
	assert(any("cow", "wow") == 1);
	assert(any("cereal", "wow") == -1);
}

int any(const char s1[], const char s2[])
{
	int i, j;
	int pos = -1;
	for (i = 0; pos == -1 && s1[i] != '\0'; i++)
	{
		for (j = 0; pos == -1 && s2[j] != '\0'; j++)
		{
			if (s1[i] == s2[j])
				pos = i;
		}
	}
	return pos;
}