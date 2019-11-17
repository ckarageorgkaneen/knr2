/*  Write a program to print a histogram of the frequencies of different characters in its input. */
#include <stdio.h>

#define MIN_ASCII 33
#define MAX_ASCII 126
#define _CHAR_MAX (MAX_ASCII-MIN_ASCII)
/* Creates a vertical histogram w freq of chars in input
 * with a max freq of 9999 */
int main()
{
	int freq_char[_CHAR_MAX + 1];
	int height = 0;
	int c, i, k;

	for (i = 0; i <= _CHAR_MAX; i++)
		freq_char[i] = 0;
	/* Set freqs of chars and set height */
	while ((c = getchar()) != EOF) {
		if (MIN_ASCII <= c && c <= MAX_ASCII) {
			++freq_char[c - MIN_ASCII];
			if (freq_char[c - MIN_ASCII] >= height)
				height = freq_char[c - MIN_ASCII];
		}
	}

	/* Iterate from height -> 0 and print freqs of char */
	for (i = height; i > 0; i--) {
		printf("%4d|", i);
		for (k = 0; k <= _CHAR_MAX; k++) {
			if (freq_char[k] >= i)
				printf("#");
			else
				printf(" ");
		}
		printf("\n");
	}

	printf("    +");
	/* Print bottom horizontal bar */
	for (i = 0; i <= _CHAR_MAX; i++) printf("-");
	printf("\n     ");

	/* Print each character */
	for (i = 0; i <= _CHAR_MAX; i++) printf("%c", i + MIN_ASCII);
	printf("\n");

	return 0;
}
