/* malloc accepts a size request without checking its plausibility; free believes that the block it is asked to free contains a valid size field. Improve these routines so they take more pains with error checking. */
#include <unistd.h>

#define MAXBYTES (unsigned) 10240
#define NALLOC 1024 /* minimum units to request */

static unsigned maxalloc; /* max number of units allocated */
static Header base; /* empty list to get started */
static Header *freep = NULL; /* start of free list */

static Header *morecore(unsigned);
char *sbrk(int);

/* malloc: general-purpose storage allocator */
void *malloc(unsigned nbytes)
{
	Header *p, *prevp;
	unsigned nunits;

	if (nbytes > MAXBYTES) {
		fprintf(stderr, "malloc: can't allocate more than %u bytes\n", MAXBYTES);
		return NULL;
	}
	nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;

	/* ... */
}

/* morecore: ask system for more memory */
static Header *morecore(unsigned nu)
{
	char *cp;
	Header *up;

	if (nu < NALLOC)
		nu = NALLOC;
	cp = sbrk(nu * sizeof(Header));
	if (cp == (char *) - 1) /* no space at all */
		return NULL;
	up = (Header *) cp;
	up->s.size = nu;

	maxalloc = (up->s.size > maxalloc) ? up->s.size : maxalloc;
	free((void *)(up + 1));
	return freep;
}

/* free: put block ap in free list */
void free(void *ap)
{
	Header *bp, *p;

	bp = (Header *)ap - 1; /* point to block header */
	if (bp->s.size == 0 || bp->s.size > maxalloc) {
		fprintf(stderr, "free: can't free %u units\n", bp->s.size);
		return;
	}
	for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)

		/* ... */
	}
