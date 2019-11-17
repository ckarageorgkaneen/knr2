/* Write a program that reads a C program and prints in alphabetical order each group of variable names that are identical in the first 6 characters but different somewhere thereafter. Don't count words within strings and comments. Make 6 a parameter that can be set from the command line. */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define YES 1
#define NO 0
#define DEF_FIRST_IDENT_NUM 6

typedef struct tnode { /* tree node */
	char *word;
	int match;
	struct tnode *l; /* left tree node */
	struct tnode *r; /* right tree node */
} tnode;

int getch(void);
void ungetch(int c);
int getword(char *word, int lim);
int comment(void);
tnode *addtree(tnode *, char *, int, int *);
int compare(char *, tnode *, int, int *);
void treeprint(tnode *);
int getword(char *, int);

/* print in alphabetical order each group of variable names
	 identical in the first num characters (default DEF_FIRST_IDENT_NUM) */
int main (int argc, char *argv[])
{
	tnode *root;
	char word[MAXWORD];
	int num;

	num = (--argc && (*++argv)[0] == '-') ? atoi(argv[0] + 1) : DEF_FIRST_IDENT_NUM;
	root = NULL;
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]) && strlen(word) >= num)
			root = addtree(root, word, num);

	treeprint(root);
	return 0;
}

/* addtree: add a node with w at or below p */
tnode *addtree(tnode *p, char *w, int num)
{
	int cond;

	if (!p) {
		p = malloc(sizeof(tnode));
		p->word = strdup(w);
		p->match = *found;
		p->l = p->r = NULL;
	}
	else if ((cond = compare(w, p, num, found)) < 0)
		p->l = addtree(p->l, w, num, found);
	else if (cond > 0)
		p->r = addtree(p->r, w, num, found);
	return p;
}

/* compare: compare words and update p->match */
int compare(char *s, tnode *p, int num, int *found)
{
	int i;
	char *t = p->word;

	for (i = 0; *s == *t; i++, s++, t++)
		if (!*s)
			return 0;
	if (i >= num)
		p->match = *found = YES;
	return *s - *t;
}

/* treeprint: in-order of tree p if p->match == YES */
void treeprint(tnode *p)
{
	if (p) {
		treeprint(p->l);
		if (p->match)
			printf("%s\n", p->word);
		treeprint(p->r);
	}
}

int getword(char *word, int lim)
{
	char c, d;
	char *w = word;

	while (isspace(c = getch()))
		;
	if (c != EOF)
		*w++ = c;
	if (isalpha(c) || c == '_' || c == '#') {
		for ( ; --lim > 0; w++)
			if (!isalnum(*w = getch()) && *w != '_') {
				ungetch(*w);
				break;
			}
	}
	else if (c == '\'' || c == '*') {
		for ( ; --lim > 0; w++)
			if ((*w = getch()) == '\\')
				*++w = getch();
			else if (*w == c) {
				w++;
				break;
			}
			else if (*w == EOF)
				break;
	}
	else if (c == '/')
		if ((d = getch()) == '*')
			c = comment();
		else
			ungetch(d);
	*w = '\0';
	return c;
}

/* comment: skip over comment and return a character */
int comment(void)
{
	int c;
	while ((c = getch()) != EOF)
		if (c == '*')
			if ((c = getch()) == '/')
				break;
			else
				ungetch(c);
	return c;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
	return bufp > 0 ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (c == EOF)
		return;

	if (bufp >= BUFSIZE)
		printf ("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}