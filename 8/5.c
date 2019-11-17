/* Modify the fsize program to print the other information contained in the inode entry. */
#include <stdio.h>
#include <string.h>
#include <fcntl.h> /* flags for read and write */
#include <sys/types.h> /* typedefs */
#include <sys/stat.h> /* structure returned by stat */
#include <dirent.h>

typedef void (*func)(char *);

void dirwalk(char *, func);

/* fsize: print inode #, mode, links, size of file "name" */
void fsize(char *name)
{
	struct stat stbuf;

	if (stat(name, &stbuf) == -1) {
		fprintf(stderr, "fsize: can't access %s\n", name);
		return;
	}
	if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
		dirwalk(name, fsize);
	printf("%5lu %6u %3lu %8ld %s\n", stbuf.st_ino,
	       stbuf.st_mode, stbuf.st_nlink, stbuf.st_size, name);
}

