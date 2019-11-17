/* Rewrite appropriate programs from earlier chapters and exercises with pointers instead of array indexing. Good possibilities include  getline (Chapters 1 and 4), atoi , itoa , and their variants (Chapters 2, 3, and 4), reverse (Chapter 3), and strindex and getop (Chapter 4). */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define _BUFSIZE 1024
#define NUMBER '0' /* signal that a number was found */

int _getline(char *s, int lim);
int _atoi(char *s);
char *__itoa(int n, char s[], int base);
void _itoa(int n, char s[]);
void reverse(char s[]);
int strrindex(char s[], char t);
int getop(char s[]);

int main()
{
  char buf[_BUFSIZE];
  assert(_getline(buf, -1) < 0);
  assert(!(_getline(buf, 5) < 0));
  printf("Got line: %s\n", buf);

  char *s = "1and2and3and4";
  assert(_atoi(s) == 1);
  __itoa(-23, buf, 10);
  assert(!strcmp(buf, "-23"));

  _itoa(-24, buf);
  assert(!strcmp(buf, "-24"));

  assert(strrindex("s is surely the char you're looking for!", 's') == 5);

  puts("Enter an int:");
  assert(getop(buf) == '0');
}

int _getline(char *s, int lim)
{
  if (lim < 0)
    return -1;

  char *p;
  int c;

  p = s;
  while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
    * p++ = c;
  if (c == '\n')
    *p++ = c;
  *p = '\0';
  return (int)(p - s);
}

int _atoi(char *s)
{
  int n, sign;

  while (isspace(*s))
    s++;
  sign = (*s == '+' || *s == '-') ? ((*s++ == '+') ? 1 : -1) : 1;
  for (n = 0; isdigit(*s); s++)
    n = (n * 10) + (*s - '0');
  return sign * n;
}

char *__itoa(int n, char s[], int base)
{
  int d = n % base;
  int r = n / base;
  if (n < 0) {
    *s++ = '-';
    d = -d;
    r = -r;
  }
  if (r)
    s = __itoa(r, s, base);
  *s++ = "0123456789abcdefghijklmnopqrstuvwxyz"[d];
  *s = '\0';
  return s;
}

void _itoa(int n, char s[]) {
  char *s_start = s;
  int i, sign = n;

  do {
    *s++ = abs(n % 10) + '0';
  } while ( n /= 10 );
  if (sign < 0)
    *s++ = '-';

  *s = '\0';
  reverse(s_start);
}

void reverse(char s[]) {
  int c, i, j;
  for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
    c = *(s + i);
    *(s + i) = *(s + j);
    *(s + j) = c;
  }
}

int strrindex(char s[], char t)
{
  int count = -1;
  for (int i = 0; * (s + i) != '\0'; i++)
    if (*(s + i) == t)
      count = i;
  return count;
}


int getch(void);
void ungetch(int);

/* getop: get next operator or numeric operand */
int getop(char s[])
{
  int i, c;

  while ((*s = c = getch()) == ' ' || c == '\t')
    ;

  *(s + 1) = '\0';
  if (!isdigit(c) && c != '.')
    return c; /* not a number */
  i = 0;
  if (isdigit(c)) /* collect integer part */
    while (isdigit(*++s = c = getch()))
      ;
  if (c == '.')
    while (isdigit(*++s = c = getch()))
      ;
  *++s = '\0';
  if (c != EOF)
    ungetch(c);
  return NUMBER;
}

#define BUFSIZE 100

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
