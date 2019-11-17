/* Revise the main routine of the longest-line program so it will correctly print the length of arbitrarily long input lines, and as much as possible of the text. */
#include <stdio.h>

#define MAXLLENGTH 100

int get_line(char line[], int limit)
{
    int i, c;
    for (i = 0; i < (limit - 1) && (( (c = getchar()) != EOF) && (c != '\n') ); i++)
        line[i] = c;
    if (i == (limit - 1)) {
        while ( (c = getchar() ) != '\n')
            ++i;
    }
    if (c == '\n') {
        line[i] = c;
        ++i;
    }
    line[i] = '\0';
    return i;
}

void copy(char to[], char from[])
{
    int i = 0;
    while ( (to[i] = from[i]) != '\0')
        ++i;
}

int main()
{
    int len, max = 0;
    char line[MAXLLENGTH], longest[MAXLLENGTH];

    while ((len = get_line(line, MAXLLENGTH)) > 0)
        if (len > max) {
            max = len;
            copy(longest, line);
        }

    if (max > 0) {
        if (max > MAXLLENGTH) {
            printf("\n\nStorage limit exceeded by : %d", max - MAXLLENGTH);
            printf("\nString length : %d", max);
            printf("\n%s", longest);
        }
        else
            printf("%s", longest);
    }

    printf("\n");
    return 0;
}
