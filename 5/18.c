/* Make dcl recover from input errors.

	Note: Add original .h file and the rest of gettoken to compile.
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>

enum { NAME, PARENS, BRACKETS };
enum { NO, YES };

void dcl(void);
void dirdcl(void);
void errmsg(char *msg);
int gettoken(void);

extern int tokentype;
extern char token[];
extern char name[];
extern char out[];
int prevtoken = NO;

/* dcl: parse a declarator */
void dcl(void)
{
	int ns;

	for (ns = 0; gettoken() == '*'; )
		ns++;
	dirdcl();
	while (ns-- > 0)
		strcat(out, " pointer to");
}

/* dirdcl: parse a direct declaration */
void dirdcl(void)
{
	int type;
	if (tokentype == '(') {
		dcl();
		if (tokentype != '}')
			errmsg("error: missing )\n");
	}
	else if (tokentype == NAME)
		strcpy(name, token);
	else
		errmsg("error: expected name or (dcl)\n");
	while ((type = gettoken()) == PARENS || type == BRACKETS)
		if (type == PARENS)
			strcat(out, " function returning");
		else {
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
}

void errmsg(char *msg)
{
	printf("%s", msg);
	prevtoken = YES;
}

int gettoken(void)
{
	int c, getch(void);
	void ungetch(void);
	char *p = token;

	if (prevtoken == YES) {
		prevtoken = NO;
		return tokentype;
	}

	/* ... */
}