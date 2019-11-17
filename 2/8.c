/* Write a function rightrot(x,n) that returns the value of the integer x rotated to the right by n bit positions.

	Example input: x=11101101 (237), n=3
	Example output: 1010 0000 0000 0000 0000 0000 0001 1101 (2684354589)
	(Assuming 64-bit architecture:
		x = 0000 0000 0000 0000 0000 0000 1110 1101)
*/
#include <stdio.h>
#include <assert.h>

unsigned rightrot(unsigned x, int n);

int main()
{
	assert(rightrot(237, 3) == 2684354589);
}

unsigned rightrot(unsigned x, int n)
{
	unsigned x_shifted = x >> n;
	unsigned dropped_bits = x & ~(~0 << n);
	unsigned shift_amount = sizeof(x) * 8 - n;
	return x_shifted | (dropped_bits << shift_amount);
}