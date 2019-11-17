/* Adapt the ideas of printd to write a recursive version of itoa ; that is, convert an integer into a string by calling a recursive routine.*/
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define BUF_SIZE 100

char *itoa(int n, char s[], int base);

int main()
{   
    char buf[BUF_SIZE];
    itoa(-23, buf, 10);
    assert(!strcmp(buf, "-23"));
}

char *itoa(int n, char s[], int base)
{
    int d = n % base;
    int r = n / base;
    if (n < 0) {
        *s++ = '-';
        d = -d;
        r = -r;
    }
    if (r)
        s = itoa(r, s, base);
    *s++ = "0123456789abcdefghijklmnopqrstuvwxyz"[d];
    *s = '\0';
    return s;
}
