/* Modify getop so that it doesn't need to use ungetch. Hint: use an internal static variable. */
#include <stdio.h>
#include <stdlib.h> /* for atof() - in K&R, math.h is referenced - this is an anachronism */

#define MAXOP 100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */

int getop(char []);
void push(double);
double pop(void);

/* reverse Polish calculator */

int main(void)
{
  int type;
  double op2;
  char s[MAXOP];

  while ((type = getop(s)) != EOF)
  {
    switch (type)
    {
    case NUMBER:
      push(atof(s));
      break;
    case '+':
      push(pop() + pop());
      break;
    case '*':
      push(pop() * pop());
      break;
    case '-':
      op2 = pop();
      push(pop() - op2);
      break;
    case '/':
      op2 = pop();
      if (op2 != 0.0)
        push(pop() / op2);
      else
        printf("error: zero divisor\n");
      break;
    case '\n':
      printf("\t%.8g\n", pop());
      break;
    default:
      printf("error: unknown command %s\n", s);
      break;
    }
  }

  return 0;
}

#define MAXVAL  100 /* maximum depth of val stack */

int sp = 0; /* next free stack position */
double val[MAXVAL]; /* value stack */

/* push: push f onto value stack */
void push(double f)
{
  if (sp < MAXVAL)
    val[sp++] = f;
  else
    printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
  if (sp > 0)
    return val[--sp];
  else
  {
    printf("error: stack empty\n");
    return 0.0;
  }
}

#include <ctype.h>

int getch(void);

/* getop: get next operator or numeric operand */
int getop(char *s)
{
  int c;
  static int buf = EOF;

  if (buf != EOF && buf != ' ' && buf != '\t'
      && !isdigit(buf) && buf != '.') {
    c = buf;
    buf = EOF;
    return c;
  }
  if (buf == EOF || buf == ' ' || buf == '\t')
    while ((*s = c = getch()) == ' ' || c == '\t')
      ;
  else
    *s = c = buf;
  buf = EOF;
  *(s + 1) = '\0';
  if (!isdigit(c) && c != '.')
    return c; /* not a number */
  if (isdigit(c)) /* collect integer part */
    while (isdigit(*++s = c = getch()))
      ;
  if (c == '.')
    while (isdigit(*++s = c = getch()))
      ;
  *++s = '\0';
  buf = c;
  return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

int getch(void) /* get a (possibly pushed back) character */
{

  return (bufp > 0) ? buf[--bufp] : getchar();
}
