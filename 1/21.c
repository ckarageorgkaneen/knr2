/* Write a program entab that replaces strings of blanks with the minimum number of tabs and blanks to achieve the same spacing. Use the same stops as for detab . When either a tab or a single blank would suffice to reach a tab stop, which should be given preference? */
#include <stdio.h>

#define TABSIZE 8

int main()
{
  int c = 0, i = 0, spaces = 0;

  while ( (c = getchar()) != EOF ) {
    if (c == ' ') {
      ++spaces;
      if (spaces == TABSIZE)
      {
        spaces = 0;
        putchar('\t');
      }
    }
    else {
      for (i = 0; i < spaces; ++i)
        putchar(' ');
      spaces = 0;
      putchar(c);
    }
  }
  return 0;
}
