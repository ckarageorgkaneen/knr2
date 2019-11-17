/* Rewrite readlines to store lines in an array supplied by main , rather than calling alloc to maintain storage. How much faster is the program? */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define MAXLINES 5000       /* maximum number of lines */
#define MAXLEN   1000       /* maximum length of a line */

char *lineptr[MAXLINES];
char lines[MAXLINES][MAXLEN];

int _getline(char s[], int lim);
int readlines(char *lineptr[], int maxlines);
int _readlines(char lines[][MAXLEN], int maxlines);

int main()
{
  puts("Enter 4 lines, the first 3 of which will be saved:");
  assert(_readlines(lines, 3) == -1);
}

/* K&R2 p29 */
int _getline(char s[], int lim)
{
  int c, i;

  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
    s[i] = c;
  if (c == '\n') {
    s[i++] = c;
  }
  s[i] = '\0';
  return i;
}

/* K&R2 p109 */
int readlines(char *lineptr[], int maxlines)
{
  int len, nlines;
  char *p, line[MAXLEN];

  nlines = 0;
  while ((len = _getline(line, MAXLEN)) > 0)
    if (nlines >= maxlines || (p = malloc(len)) == NULL)
      return -1;
    else {
      line[len - 1] = '\0';  /* delete the newline */
      strcpy(p, line);
      lineptr[nlines++] = p;
    }
  return nlines;
}

int _readlines(char lines[][MAXLEN], int maxlines)
{
  int len, nlines;

  nlines = 0;
  while ((len = _getline(lines[nlines], MAXLEN)) > 0)
    if (nlines >= maxlines)
      return -1;
    else
      lines[nlines++][len - 1] = '\0';  /* delete the newline */
  return nlines;
}
