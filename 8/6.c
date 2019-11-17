/* The standard library function calloc(n,size) returns a pointer to n objects of size size , with the storage initialized to zero. Write calloc , by calling malloc or by modifying it. */
#include <stdio.h>
#include <stdlib.h>

/* calloc: allocate n objects of size size */
void *calloc(unsigned n, unsigned size)
{
	unsigned i, nb;
	char *p, *q;

	nb = n * size;
	if ((p = q = malloc(nb)) != NULL)
		for (i = 0; i < nb; i++)
			*p++ = 0;
	return q;
}
