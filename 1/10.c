/* Write a program to copy its input to its output, replacing each tab by \t , each backspace by \b , and each backslash by \\ . This makes tabs and backspaces visible in an unambiguous way. */
#include <stdio.h>

#define dputchar(x,y); putchar(x);putchar(y);

int main()
{
  int c = EOF;
  while ((c = getchar()) != EOF) {
    switch (c) {
    case '\t':
      dputchar('\\', 't');
      break;
    case '\b':
      dputchar('\\', 'b');
      break;
    case '\\':
      dputchar('\\', '\\');
      break;
    default:
      putchar(c);
      break;
    }
  }
  return 0;
}

