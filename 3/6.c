/* Write a version of itoa that accepts three arguments instead of two. The third argument is a minimum field width; the converted number must be padded with blanks on the left if necessary to make it wide enough. */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

#define BUF_SIZE 20
#define MIN_FIELD_WIDTH 7

void itoa(int n, char s[], int width);
void reverse(char s[]);

int main(void) {
    char buffer[BUF_SIZE];
    char *ptr;
    //printf("INT_MIN: %d\n", INT_MIN);
    itoa(INT_MIN, buffer, MIN_FIELD_WIDTH);
    // printf("Buffer : %s\n", buffer);
    assert(strtol(buffer, &ptr, 10) == (long int)INT_MIN);

    return 0;
}

void itoa(int n, char s[], int width) {
    int i, sign;
    sign = n;

    i = 0;
    do {
        s[i++] = abs(n % 10) + '0';
    } while ( n /= 10 );
    if (sign < 0)
        s[i++] = '-';

    while (i < width )    /*  Only addition to original function  */
        s[i++] = ' ';

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