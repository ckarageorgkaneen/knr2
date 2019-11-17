#include <stdio.h>
#include <stdlib.h>

#define TABSIZE 8

int main(int argc, char *argv[])
{
    int c, pos, i;
    int tabsize[2] = {TABSIZE, TABSIZE};

    while (--argc > 0 && (**++argv == '-' || **argv == '+'))
        switch (**argv) {
        case '-':
            if ((pos = atoi(*argv + 1)) > 0)
                tabsize[0] = pos;
            break;
        case '+':
            if ((pos = atoi(*argv + 1)) > 0)
                tabsize[1] = pos;
            break;
        }

    pos = i = 0;

    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            while (pos < tabsize[i]) {
                putchar(' ');
                ++pos;
            }
            pos = 0;
            if (i < 1)
                i++;
        }
        else {
            putchar(c);

            if (c == '\n')
                pos = i = 0;
            else {
                pos++;

                if (pos == tabsize[i]) {
                    pos = 0;
                    if (i < 1)
                        i++;
                }
            }
        }
    }

    return 0;
}

