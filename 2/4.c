/* Write an alternate version of squeeze(s1,s2) that deletes each character in the string s1 that matches any character in the string s2 . */
#include <stdio.h>
#include <string.h>
#include <assert.h>

char * squeeze(char s1[], const char s2[]);

int main()
{
  char s1[] = "somebody";
  const char *s2 = "sandwhich";
  char *new_s1 = squeeze(s1, s2);
  assert(!strcmp(new_s1, "omeboy"));
}

char * squeeze(char s1[], const char s2[]) {
  int i, j, k;
  for (k = 0; s2[k] != '\0'; k++) {
    for (i = j = 0; s1[i] != '\0'; i++)
      if (s1[i] != s2[k])
        s1[j++] = s1[i];
    s1[j] = '\0';
  }
  return s1;
}