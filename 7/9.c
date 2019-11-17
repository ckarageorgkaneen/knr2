/* Functions like isupper can be implemented to save space or to save time. Explore both possibilities. */
#include <stdio.h>
#define isupper(c) ((c) >= 'A' && (c) <= 'Z')
/* int isupper(char c)
{
	return (c >= 'A' && c <= 'Z')
}*/

int main()
{
	printf("%d", isupper('H'));
}
