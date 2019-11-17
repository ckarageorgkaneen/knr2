/* Write a function expand(s1,s2) that expands shorthand notations like a-z in the string s1 into the equivalent complete list abc...xyz in s2 . Allow for letters of either case and digits, and be prepared to handle cases like a-b-c and a-z0-9 and -a-z . Arrange that a leading or trailing - is taken literally.

    Note: Add an extra check (using strchr) if you want to include illegal ranges (a-9, 3-X, etc.)
*/

#include <stdio.h>
#define BUF_SIZE 250

void expand(char s1[], char s2[]);

int main()
{
    char s1[BUF_SIZE] = "-a-z p-b 0-9 66-12 a-d-f -0-2 some text 1-1 WITH CAPITALS! 0-0 5-3 -";
    char s2[BUF_SIZE];

    expand(s1, s2);
    printf("%s\n", s2);
}

void expand(char s1[], char s2[])
{
    char c, d;
    int i, j;
    i = j = 0;

    while ((c = s1[i++]) != '\0') {
        if (c != ' ' && s1[i] == '-' && s1[i + 1] != '\0') {
            if (c > (d = s1[++i]))
                while (c > d)
                    s2[j++] = c--;
            else
                while (c < d)
                    s2[j++] = c++;
        }
        else
            s2[j++] = c;
    }
    s2[j] = '\0';
}