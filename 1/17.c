/* Write a program to print all input lines that are longer than 80 characters. */
#include <stdio.h>
#define LLENGTH_AT_LEAST 10
#define LLENGTH_AT_MOST 1000

int get_line(char line[], int llimit)
{
	int i, c;
	for (i = 0; i < (llimit - 1) && (( (c = getchar()) != EOF) && (c != '\n') ); i++)
		line[i] = c;

	if (c == '\n')
		line[i++] = c;

	line[i] = '\0';
	return i;
}

int main()
{
	int len;
	char line[LLENGTH_AT_MOST];
	int line_counter = 1;

	while ((len = get_line(line, LLENGTH_AT_MOST)) > 0) {
		if (len > LLENGTH_AT_LEAST) {
			printf("L%d: %s", line_counter++ , line);
		}
	}

	printf("Total # Lines > 80 chars: %d\n", line_counter - 1);
	return 0;
}
