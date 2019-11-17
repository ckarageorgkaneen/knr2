/* Write the program expr , which evaluates a reverse Polish expression from the command line, where each operator or operand is a separate argument. For example,
	expr 2 3 4 + *
	evaluates 2 X (3 + 4).

  Note: Use \* instead of * when running, e.g. ./10 2 3 4 + \* instead of ./10 2 3 4 + *,
  since * is a shell wildcard.
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define STACKSIZE 1024

void ohno(const char *msg);
void push(double value);
double pop(void);

int main(int argc, char *argv[])
{
	int i;
	double value;

	for (i = 1; i < argc; i++) {
		switch (argv[i][0]) {
		case '\0':
			ohno("empty cl arg");
			break;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			push(atof(argv[i]));
			break;
		case '+':
			push(pop() + pop());
			break;
		case '-':
			value = pop();
			push(pop() - value);
			break;
		case '*':
			push(pop() * pop());
			break;
		case '/':
			value = pop();
			push(pop() / value);
			break;
		default:
			ohno("unknown op");
			break;
		}
	}

	printf("%g\n", pop());
	return 0;
}

double stack[STACKSIZE];
int sp = 0;

void ohno(const char *msg)
{
	fprintf(stderr, "%s\n", msg);
	exit(EXIT_FAILURE);
}

void push(double value)
{
	if (sp == STACKSIZE)
		ohno("stack is full!");
	stack[sp++] = value;
}

double pop(void)
{
	if (!sp)
		ohno("stack is empty!");
	return stack[--sp];
}
