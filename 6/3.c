/* Write a cross-referencer that prints a list of all words in a document, and, for each word, a list of the line numbers on which it occurs. Remove noise words like "the," "and," and so on. */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXWORD 100

typedef struct llist { /* linked list of line numbers */
	int lnum;
	struct llist *next;
} llist;

typedef struct tnode {
	char *word;
	struct llist *lines;
	struct tnode *l;
	struct tnode *r;
} tnode;

int getch(void);
void ungetch(int c);
int getword(char *word, int lim);
int comment(void);
tnode *addtree(tnode *, char *, int);
int compare(char *, tnode *, int, int *);
int noiseword(char *);
void treeprint(tnode *);
void addln(tnode *, int);

int main()
{
	tnode *root;
	char word[MAXWORD];
	int linenum = 1;

	root = NULL;
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]) && noiseword(word) == -1)
			root = addtree(root, word, linenum);
		else if (word[0] == '\n')
			linenum++;
	treeprint(root);
	return 0;
}

/* addtree: add a node with w at or below p */
tnode *addtree(tnode *p, char *w, int linenum)
{
	int cond;

	if (!p) {
		p = (tnode *)malloc(sizeof(tnode));
		if (!p)
			fprintf(stderr, "malloc ERROR!\n");
		p->word = strdup(w);
		p->lines = (llist *)malloc(sizeof(llist));
		p->lines->lnum = linenum;
		p->lines->next = NULL;
		p->l = p->r = NULL;
	}
	else if ((cond = strcmp(w, p->word)) == 0)
		addln(p, linenum);
	else if (cond < 0)
		p->l = addtree(p->l, w, linenum);
	else
		p->r = addtree(p->r, w, linenum);
	return p;
}

/* addln: add a line number to the linked list */
void addln(tnode *p, int linenum)
{
	llist *temp = p->lines;
	while (temp->next && temp->lnum != linenum)
		temp = temp->next;
	if (temp->lnum != linenum) {
		temp->next = (llist *)malloc(sizeof(llist));
		if (!temp->next)
			fprintf(stderr, "malloc ERROR!\n");
		temp->next->lnum = linenum;
		temp->next->next = NULL;
	}
}

/* treeprint: in-order tree print */
void treeprint(tnode *p)
{
	if (p) {
		treeprint(p->l);
		printf("%10s: ", p->word);
		for (llist *temp = p->lines; temp != NULL; temp = temp->next)
			printf("%4d ", temp->lnum);
		printf("\n");
		treeprint(p->r);
	}
}

/* noiseword: identify w as a noise word */
int noiseword(char *w)
{
	static char *nw[] = {
		"a",
		"an",
		"and",
		"are",
		"in",
		"is",
		"of",
		"or",
		"that",
		"the",
		"this",
		"to"
	};
	int cond, mid;
	int low = 0;
	int high = sizeof(nw) / sizeof(char *) - 1;

	while (low <= high) {
		mid = (low + high) / 2;
		if ((cond = strcmp(w, nw[mid])) < 0)
			high = mid - 1;
		else if (cond > 0)
			low = mid + 1;
		else
			return mid;
	}
	return -1;
}

int getword(char *word, int lim)
{
	char c, d;
	char *w = word;

	while (isspace(c = getch()) && c != '\n')
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
