/* Write a program that prints its input one word per line. */
#include <stdio.h>

int main(void)
{
    int c, extra_space = 1;

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\t' || c == '\n') {
            if (!extra_space) {
                extra_space = 1;
                putchar('\n');
            }
        } else {
            extra_space = 0;
            putchar(c);
        }
    }

    return 0;
}
