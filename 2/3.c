/* Write the function htoi(s) , which converts a string of hexadecimal digits (including an optional 0x or 0X) into its equivalent integer value. The allowable digits are 0 through 9, a through f, and A through F .*/
#include <stdio.h>
#include <ctype.h>
#include <assert.h>

unsigned long htoi(const char h[]);

int main()
{
	assert(htoi("F00") == 3840);
	assert(htoi("0xdeadbeef") == 3735928559);
}

unsigned long htoi(const char h[])
{
	unsigned long i = 0;

	for (int idx = 0; h[idx] != '\0'; idx++) {
		char c = tolower(h[idx]);
		char next_c = tolower(h[idx + 1]);

		int starts_w_zerox = c == '0' && next_c == 'x';
		int is_num = c >= '0' && c <= '9';
		int is_letter = c >= 'a' && c <= 'f';

		if (starts_w_zerox)
			idx++;
		else if (is_num)
			i =  16 * i + (c - '0');
		else if (is_letter)
			i = 16 * i + (c - 'a' + 10);
	}

	return i;
}
