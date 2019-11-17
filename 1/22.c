/* Write a program to "fold" long input lines into two or more shorter lines after the last non-blank character that occurs before the n -th column of input. Make sure your program does something intelligent with very long lines, and if there are no blanks or tabs before the specified column.  */
#include <stdio.h>

#define MAXLINE 1000 /* max input line size */
#define FOLDLENGTH 20 /* The max length of a line */

int getline(char line[], int lim)
{
	int c, i;

	for ( i = 0; i < lim - 1 && ( c = getchar()) != EOF && c != '\n'; ++i)
		line[i] = c;
	if (c == '\n') {
		line[i] = c;
		++i;
	}
	line[i] = '\0';
	return i;
}

int main()
{
	int pos, len;
	int line_pos, spaceholder;
	char line[MAXLINE]; /*current input line*/

	while (( len = getline(line, MAXLINE)) > 0 ) {
		if ( len >= FOLDLENGTH ) {
			/* If this is an extra long line then we
			** loop through it replacing a space nearest
			** to the foldarea with a newline.
			*/
			pos = 0;
			line_pos = 0;
			while (pos < len) {
				if (line[pos] == ' ')
					spaceholder = pos;

				if (line_pos == FOLDLENGTH) {
					line[spaceholder] = '\n';
					line_pos = 0;
				}
				line_pos++;
				pos++;
			}
		}
		printf ( "%s", line);
	}
	return 0;
}