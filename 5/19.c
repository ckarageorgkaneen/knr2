/* Modify undcl so that it does not add redundant parentheses to declarations.

Note: Add original .h and .c files to compile
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
#define MAXOUT 1000

enum { NAME, PARENS, BRACKETS };
enum { NO, YES };

void dcl(void);
void dirdcl(void);
int gettoken(void);
int nexttoken(void);

int tokentype;
char token[MAXTOKEN];
char out[MAXOUT];

int main()
{
	int type;
	char temp[MAXTOKEN];

	while (gettoken() != EOF) {
		strcpy(out, token);
		while ((type = gettoken()) != '\n')
			if (type == PARENS || type == BRACKETS)
				strcat(out, token);
			else if (type == '*') {
				if ((type = nexttoken()) == PARENS || type == BRACKETS)
					sprintf(temp, "(*%s)", out);
				else
					sprintf(temp, "*%s", out);
			}
			else if (type == NAME) {
				sprintf(temp, "%s %s", token, out);
				strcpy(out, temp);
			}
			else
				printf("invalid input at %s\n", token);
		printf("%s\n", out);
	}
	return 0;
}

int nexttoken(void)
{
	int type;
	extern int prevtoken;

	type = gettoken();
	prevtoken = YES;
	return type;
}
