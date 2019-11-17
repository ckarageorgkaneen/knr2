/* Write a pointer version of the function strcat that we showed in Chapter 2: strcat(s,t) copies the string t to the end of s .

 Original:
 void strcat(char s[], char t[])
 {
 		int i, j;
 		i = j = 0;
 		while (s[i] != '\0')
 			i++;
 		while ((s[i++] = t[j++]) != '\0')
 			;
 }
*/
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define STRSIZE 1024

void _strcat(char *s, char *t);

int main()
{
	char name[STRSIZE] = "Chris";
	char space[] = " ";
	char surname[] = "Karageorgiou Kaneen";
	_strcat(name, space);
	_strcat(name, surname);
	assert(!strcmp(name, "Chris Karageorgiou Kaneen"));
}

void _strcat(char *s, char *t)
{
	while (*s++); --s;
	while (*s++ = *t++);
}
