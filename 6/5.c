/* Write a function undef that will remove a name and definition from the table maintained by lookup and install . */
unsigned hash(char *);

/* undef: remove a name and definition from the table */
void undef(char *s)
{
	int h;
	struct nlist *prev, *np;

	prev = NULL;
	h = hash(s); /* hash value of s */
	for (np = hashtable[h]; np; np = np->next) {
		if (!strcmp(s, np->name))
			break;
		prev = np;
	}

	if (np) {
		if (prev == NULL)
			hashtable[h] = np->next;
		else
			prev->next = np->next;
		free(np->name);
		free(np->defn);
		free(np);
	}
}
