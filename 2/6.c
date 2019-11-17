/* Write a function setbits(x,p,n,y) that returns x with the n bits that begin at position p set to the rightmost n bits of y, leaving the other bits unchanged.

	Example input: x=10011101 (157), p=4, n=3, y=10010101 (149)
	Example output: 10010101 (149)
*/
#include <stdio.h>
#include <assert.h>

unsigned setbits(unsigned x, int p, int n, unsigned y);

int main()
{
	assert(setbits(157, 4, 3, 149) == 149);
}

unsigned setbits(unsigned x, int p, int n, unsigned y)
{
	unsigned rmost_n_ones = ~(~0 << n); // 00000111
	unsigned x_mask = ~(rmost_n_ones << p + 1 - n); // 11100011
	unsigned x_masked = x & x_mask; // 10000001 (= 10011101 & 11100011)
	unsigned rmost_n_bits_of_y = rmost_n_ones & y; // 00000101
	unsigned y_mask = rmost_n_bits_of_y << p + 1 - n; // 00010100

	return x_masked | y_mask; // 10010101 (= 10000001 | 00010100)
}