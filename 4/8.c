/* Suppose there will never be more than one character of pushback. Modify getch and ungetch accordingly. */
#include <string.h>
#include <stdio.h>
#include <assert.h>

#define BUFSIZE 1

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

int getch(void) /* get a (possibly pushed back) character */
{
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}

void ungets(const char *s)
{
  size_t i = strlen(s);

  while (i > 0)
    ungetch(s[--i]);
}

int main(void)
{
  char *s = "Chris";
  int c, i = 0;

  ungets(s);
  while ((bufp > 0) && (c = getch()))
    assert(s[i++] == c);
  return 0;
}
