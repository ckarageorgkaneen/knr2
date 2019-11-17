/*  Experiment to find out what happens when printf 's argument string contains \c, where c is some character not listed above. */
#include <stdio.h>

int main()
{
  printf("alert (0x07) - added in C89: '\a'\n");
  printf("backspace (0x08): ' \b'\n");
  printf("horizontal tab (0x09): '\t'\n");
  printf("newline (0x0A): '\n'\n");
  printf("vertical tab (0x0B):'\v'\n");
  printf("formfeed (0x0C): '\f'\n");
  printf("carriage return (0x0D): '\r'\n");
  printf("double quote: (0x22)'\"'\n");
  printf("single quote (0x27): '\''\n");
  printf("question mark (0x3F): '\?'\n");
  printf("backslash (0x5C): '\\'\n");
  printf("octal number (nnn): '\101'\n");
  printf("hexadecimal number(xhh): '\x01'\n");
  printf("escape sequence: '\e'\n");

  return 0;
}
