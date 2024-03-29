/* Write the function itob(n,s,b) that converts the integer n into a base b character representation in the string s . In particular, itob(n,s,16) formats n as a hexadecimal integer in s. */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#define NUMBER 255
#define BUF_SIZE 10

void itob(int n, char s[], int b);
void reverse(char s[]);

int main(void) {
    char buffer[BUF_SIZE];
    int base;
    char *ptr;
    for ( base = 2; base <= 36; ++base ) {
        itob(NUMBER, buffer, base);
        assert(strtol(buffer, &ptr, base) == (long int)NUMBER);
    }
    return 0;
}


/*  Stores a string representation of integer n
    in s[], using a numerical base of b. Will handle
    up to base-36 before we run out of digits to use.  */

void itob(int n, char s[], int b) {
    static char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int i, sign;

    if ( b < 2 || b > 36 ) {
        fprintf(stderr, "EX3_5: Cannot support base %d\n", b);
        exit(EXIT_FAILURE);
    }

    if ((sign = n) < 0)
        n = -n;
    i = 0;
    do {
        s[i++] = digits[n % b];
    } while ((n /= b) > 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}


/*  Reverses string s[] in place  */

void reverse(char s[]) {
    int c, i, j;
    for ( i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
