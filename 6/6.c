/* Implement a simple version of the #define processor (i.e., no arguments) suitable for use with C programs, based on the routines of this section. You may also find getch and ungetch helpful.

	Note: undefined functions are defined in previous exercises and K&R. ommitted due to pure slackness.
*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100

typedef struct nlist {
	struct nlist *next;
	char *name;
	char *defn;
} nlist;

void error(int, char*);
int getch(void);
void getdef(void);
int getword(char *, int);
nlist *install(char *, char *);
nlist *lookup(char *);
void skipblanks(void);
void undef(char *);
void ungetch(int);
void ungets(char *);

/* simple #define processor */
int main()
{
	char w[MAXWORD];
	struct nlist *p;

	while (getword(w, MAXWORD) != EOF)
		if (strcmp(w, "#") == 0)
			getdef();
		else if (!isalpha(w[0]))
			printf("%s", w); /* cannot be defined */
		else if ((p = lookup(w)) == NULL)
			printf("%s", w); /* not defined */
		else
			ungets(p->defn); /* push definition */
	return 0;
}

/* getdef: get definition and install it */
void getdef(void)
{
	int c, i;
	char def[MAXWORD], dir[MAXWORD], name[MAXWORD];

	skipblanks();
	if (!isalpha(getword(dir, MAXWORD)))
		error(dir[0],
		      "getdef: expecting a directive after #");
	else if (strcmp(dir, "define") == 0) {
		skipblanks();
		if (!isalpha(getword(name, MAXWORD)))
			error(name[0],
			      "getdef: non-alpha - name expected");
		else {
			skipblanks();
			for (i = 0; i < MAXWORD - 1; i++)
				if ((def[i] = getch()) == EOF || def[i] == '\n')
					break; /* end of definition */
			def[i] = '\0';
			if (i <= 0) /* no definition */
				error('\n', "getdef: incomplete define");
			else /* install definition */
				install(name, def);
		}
	} else if (strcmp(dir, "undef") == 0) {
		skipblanks();
		if (!isalpha(getword(name, MAXWORD)))
			error(name[0], "getdef: non-alpha in undef");
		else
			undef(name);
	} else
		error(dir[0], "getdef: expecting a directive after #");
}

void error(int c, char *s)
{
	fprintf(stderr, "error: %s\n", s);
	while (c != EOF && c != '\n')
		c = getch();
}

/* skipblanks: skip blank and tab characters */
void skipblanks(void)
{
	int c;
	while ((c = getch()) == ' ' || c == '\t')
		;
	ungetch(c);
}
