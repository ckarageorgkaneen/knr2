/* In a two's complement number representation, our version of itoa does not handle the largest negative number, that is, the value of n equal to -(2 to the power (wordsize - 1)) . Explain why not. Modify it to print that value correctly regardless of the machine on which it runs.

     "An N-bit ones' complement numeral system can only represent integers in the range
     −[[2^(N−1)]−1] to [2^(N−1)]−1 while two's complement can express −2^(N−1) to 2^(N−1)−1."

     Assuming N=8, the largest negative number is −2^(N−1) = -128, which in 2's complement
     has no positive equivalent +128 (its 2's complement is itself).

     Thus, the absolute value of the largest negative number cannot be represented
     (i.e. we cannot represent +128). Since the itoa() function in Chapter 3 handles negative numbers by reversing the
     sign of the number before processing, then adding a '-' to the string,
     passing the largest negative number will result it in being translated to itself (-128).

     Therefore, because (n /= 10) will be negative, the do-while loop will run once only,
     and will place in the string a '-', followed by a single character, (INT_MIN % 10 + '0').
     We can remedy these two bugs in the following way: 1 - change 'while ((n /= 10) > 0)' to
     'while (n /= 10)'. Since any fractional part is truncated with integer division,
     n will eventually equal zero after successive divides by 10, and 'n /= 10' will
     evaluate to false sooner or later. 2 - change 'n % 10 + '0 to 'abs(n % 10) + '0,
     to get the correct character. EX3_4.C shows the revised function, which will run
     correctly regardless of the number representation.
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

#define BUF_SIZE 20

void itoa(int n, char s[]);
void reverse(char s[]);

int main(void) {
    char buffer[BUF_SIZE];
    char *ptr;
    //printf("INT_MIN: %d\n", INT_MIN);
    itoa(INT_MIN, buffer);
    // printf("Buffer : %s\n", buffer);
    assert(strtol(buffer, &ptr, 10) == (long int)INT_MIN);

    return 0;
}

void itoa(int n, char s[]) {
    int i, sign;
    sign = n;

    i = 0;
    do {
        s[i++] = abs(n % 10) + '0';
    } while ( n /= 10 );
    if (sign < 0)
        s[i++] = '-';

    s[i] = '\0';
    reverse(s);
}

void reverse(char s[]) {
    int c, i, j;
    for ( i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}