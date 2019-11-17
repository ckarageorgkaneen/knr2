/* Rewrite the function lower, which converts upper case letters to lower case, with a conditional expression instead of if-else.

  Note: conditional expression: aka ternary operator
*/
#include <stdio.h>
#include <assert.h>

int lower(int);

int main()
{
	assert(lower('K') == 'k');
	assert(lower('l') == 'l');
}

int lower(int c)
{
	return (c >= 'A' && c <= 'Z') ? (c + 'a' - 'A') : c;
}