/* Write a program to print a histogram of the lengths of words in its input. It is easy to draw the histogram with the bars horizontal; a vertical orientation is more challenging. */
#include <stdio.h>

#define MAX_WL 10
#define _neww_l_index(neww_l) \
    ((neww_l) > MAX_WL ? MAX_WL : (neww_l))
#define _histogram(word_length)                                               \
for(unsigned int i = 0; i < sizeof(word_length)/sizeof(word_length[0]); i++){ \
        printf("\n|%d|:", i + 1);                                             \
        for(int j = 0; j < word_length[i]; j++)                               \
            printf("*");                                                      \
}

int main(void)
{
    int c, neww_l = 0;
    int extra_space = 1;
    int word_length[MAX_WL] = { 0 };

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\t' || c == '\n') {
            if (!extra_space) {
                if (neww_l) {
                    word_length[_neww_l_index(neww_l) - 1]++;
                    neww_l = 0;
                }
                extra_space = 1;
            }
        } else {
            extra_space = 0;
            neww_l++;
        }
    }

    _histogram(word_length);

    return 0;
}
