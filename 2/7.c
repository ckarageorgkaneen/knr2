/* Write a function invert(x,p,n) that returns x with the n bits that begin at position p inverted (i.e., 1 changed into 0 and vice versa), leaving the others unchanged.

	Example input: x=11111111 (255), p=4, n=3
	Example output: 11100011 (227)
*/
#include <stdio.h>
#include <assert.h>

unsigned invert(unsigned x, int p, int n);

int main()
{
	assert(invert(255, 4, 3) == 227);
}

unsigned invert(unsigned x, int p, int n)
{
	unsigned rmost_n_ones = ~(~0 << n); // 00000111
	unsigned mask = rmost_n_ones << p + 1 - n; // 00011100

	return x ^ mask; // 11100011(= 11111111 ^ 00011100)
}