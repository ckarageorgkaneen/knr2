/* Write a program that prints the distinct words in its input sorted into decreasing order of frequency of occurrence. Precede each word by its count. */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 100
#define NDISTINCT 1000

typedef struct tnode {
	char *word;
	int count;
	struct tnode *l;
	struct tnode *r;
} tnode;

int getch(void);
void ungetch(int c);
int getword(char *word, int lim);
tnode *addtree(tnode *, char *);
int getword(char *, int);
void sortlist(void);
void treestore(tnode *);

tnode *list[NDISTINCT];
int ntn = 0;

/* print distinct words sorted in decreasing order of freq. */
int main()
{
	tnode *root;
	char word[MAXWORD];
	int i;

	root = NULL;
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			root = addtree(root, word);
	treestore(root);
	sortlist();
	for (i = 0; i < ntn; i++)
		printf("%2d:%20s\n", list[i]->count, list[i]->word);
	return 0;
}

/* treestore: store in list[] tree node pointers */
void treestore(tnode *p)
{
	if (p) {
		treestore(p->l);
		if (ntn < NDISTINCT)
			list[ntn++] = p;
		treestore(p->r);
	}
}

/* sortlist: sort list of pointers to tree nodes in descreasing order of frequency of occurence */
void sortlist()
{
	int gap, i, j;
	tnode *temp;

	for (gap = ntn / 2; gap > 0; gap /= 2)
		for (i = gap; i < ntn; i++)
			for (j = i - gap; j >= 0; j -= gap) {
				if ((list[j]->count) >= (list[j + gap]->count))
					break;
				temp = list[j];
				list[j] = list[j + gap];
				list[j + gap] = temp;
			}
}

/* addtree: add a node with w at or below p */
tnode *addtree(tnode *p, char *w)
{
	int cond;

	if (!p) {
		p = (tnode *)malloc(sizeof(tnode));
		if (!p)
			fprintf(stderr, "malloc ERROR!\n");
		p->word = strdup(w);
		p->count = 1;
		p->l = p->r = NULL;
	}
	else if ((cond = strcmp(w, p->word)) == 0)
		p->count++;
	else if (cond < 0)
		p->l = addtree(p->l, w);
	else
		p->r = addtree(p->r, w);
	return p;
}

/* getword:  get next word or character from input */
int getword(char *word, int lim)
{
	int c, getch(void);
	void ungetch(int);
	char *w = word;

	while (isspace(c = getch()))
		;
	if (c != EOF)
		*w++ = c;
	if (!isalpha(c)) {
		*w = '\0';
		return c;
	}
	for ( ; --lim > 0; w++)
		if (!isalnum(*w = getch())) {
			ungetch(*w);
			break;
		}
	*w = '\0';
	return word[0];
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
