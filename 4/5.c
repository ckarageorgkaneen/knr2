/* Add access to library functions like sin , exp , and pow . See <math.h> in Appendix B, Section 4. */
#include <stdio.h>
#include <stdlib.h> /* for atof() - in K&R, math.h is referenced - this is an anachronism */
#include <string.h>
#include <math.h>

#define MAXOP 100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define IDENTIFIER '1' /* signal that id was found */

int my_getop(char []);
void push(double);
double pop(void);
void print_top(void);
void dup_top(void);
void swap_top(void);
void clear_stack();
void push_special_math_val(char s[]);

/* reverse Polish calculator */

int main(void)
{
  int type;
  double op2;
  char s[MAXOP];

  while ((type = my_getop(s)) != EOF)
  {
    switch (type)
    {
    case NUMBER:
      push(atof(s));
      puts("Pushed");
      break;
    case IDENTIFIER:
      push_special_math_val(s);
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
    case '%':
      op2 = pop();
      if (op2)
        push(fmod(pop(), op2));
      else
        printf("\nError: Division by zero!");
      break;
    case '?':
      print_top();
      break;
    case '#':
      dup_top();
      break;
    case '~':
      swap_top();
      break;
    case '!':
      clear_stack();
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

void print_top(void)
{
  if (sp > 0)
    printf("Top of stack: %8g\n", val[sp - 1]);
  else
    printf("Stack is empty.\n");
}

void dup_top(void)
{
  double _val = pop();
  push(_val);
  push(_val);
}

void swap_top(void)
{
  double val1 = pop();
  double val2 = pop();
  push(val1);
  push(val2);
}

void clear_stack(void)
{
  sp = 0; // simply clear pointer
}

void push_special_math_val(char s[])
{
  double op2;
  if (!strcmp(s, "sin"))
    push(sin(pop()));
  else if (!strcmp(s, "cos"))
    push(cos(pop()));
  else if (!strcmp(s, "exp"))
    push(exp(pop()));
  else if (!strcmp(s, "pow")) {
    op2 = pop();
    push(pow(pop(), op2));
  }
  else
    printf("%s is not a supported function.\n", s);
}

#include <ctype.h>

int getch(void);
void ungetch(int);

/* getop: get next operator or numeric operand */
int my_getop(char s[])
{
  int i, c, next;

  while ((s[0] = c = getch()) == ' ' || c == '\t')
    ;

  s[1] = '\0';

  if (isalpha(c))
  {
    i = 0;
    while (isalpha(s[i++] = c ))
      c = getch();
    s[i - 1] = '\0';
    if (c != EOF)
      ungetch(c);
    return IDENTIFIER;
  }

  if (!isdigit(c) && c != '.' /* add this: */ && c != '-')
    return c; /* not a number */

  if (c == '-') {
    next = getch();
    if (!isdigit(next) && next != '.')
      return c;
    c = next;
  }
  else
    c = getch();
  i = 0;
  while (isdigit(s[++i] = c))
    c = getch();
  if (c == '.')
    while (isdigit(s[++i] = c = getch()))
      ;
  s[i] = '\0';
  if (c != EOF)
    ungetch(c); /* push unto ungetch buffer */
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


