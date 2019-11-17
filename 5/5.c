/* Write versions of the library functions strncpy , strncat , and strncmp , which operate on at most the first n characters of their argument strings. For example, strncpy(s,t,n) copies at most n characters of t to s . Full descriptions are in Appendix B
 
 Description:
 char *strncpy(s,ct,n)	copy at most n characters of string c
				to s, return s. Pad with '\0's is c
				has fewer than n characters
 char *strncat(s,ct,n)	concatenate at most n characters o
				string ct to string s, terminate s wit
				'\0'; return s
 int strncmp(cs,ct,n)	compare at most n characters of strin
				cs to string ct; return <0 if cs<ct
				0 if cs==ct, or >0 if cs>ct
*/
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define STRSIZE 1024

char *_strncpy(char *s, char *t, int n);
char *_strncat(char *s, char *t, int n);
int _strncmp(char *s, char *t, int n);

int main()
{
	char name[] = "Chrissss";
	char s[] = "KK   ";
	assert(!strcmp(_strncpy(name, name, 5), "Chris"));
	assert(!strcmp(_strncat(name, s, 2), "ChrisKK"));
	assert(!_strncmp("Jesus", "Jessy", 3));
}

char *_strncpy(char *s, char *t, int n)
{
	int i;
	char *s_start = s;

	for (i = 0; i < n && (*s++ = *t++); i++)
		;
	if (i == n)
		*s = '\0';
	return s_start;
}

char *_strncat(char *s, char *t, int n)
{
	int i;
	char *s_start = s;

	while (*++s)
		;
	for (i = 0; i < n && (*s++ = *t++); i++)
		;
	*s = '\0';
	return s_start;
}

int _strncmp(char *s, char *t, int n)
{
	int i;

	for (i = 0; i < n; i++)
		if (s[i] != t[i] || s[i] == 0 || t[i] == 0)
			return s[i] - t[i];
	return 0;
}
