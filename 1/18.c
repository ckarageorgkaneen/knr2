/* Write a program to remove all trailing blanks and tabs from each line of input, and to delete entirely blank lines. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define BUF_SIZE 1000

int main()
{
	char buffer[BUF_SIZE];
	char *line = buffer;
	size_t line_buf_size = BUF_SIZE;
	size_t line_size, last_char_idx, cur_null_term_idx, cur_newline_idx;

	while ( (line_size = getline(&line, &line_buf_size, stdin)) != -1 ) {
		if (line_size > line_buf_size) {
			printf("FAULT: line longer than BUF_SIZE!\n");
			exit(1);
		}
		assert(line[line_size] == '\0');
		assert(line[line_size - 1] == '\n');

		cur_null_term_idx = line_size;
		cur_newline_idx = line_size - 1;
		last_char_idx = (int)(line_size - 2) >= 0 ? (line_size - 2) : 0 ;

		for (size_t i = last_char_idx; i > 0; i--) {
			if (!(line[i] == ' ' || line[i] == '\t')) {
				// Clear current newline and null term
				line[cur_newline_idx] = '\0';
				line[cur_null_term_idx] = '\0';
				// Set new null term.
				line[i + 1] = '\n';
				line[i + 2] = '\0';

				printf("%s", line);
				break;
			}
		}

		memset(line, 0, sizeof line);
	}

	return (0);
}
