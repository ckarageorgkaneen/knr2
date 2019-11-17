/* How would you test the word count program? What kinds of input are most likely to uncover bugs if there are any? Basic unit testing. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

#define strlitconcat(x,y) x y
#define TEST_DIR "ex_11_tests/"

char* concat(const char *s1, const char *s2)
{
  const size_t len1 = strlen(s1);
  const size_t len2 = strlen(s2);
  char *result = malloc(len1 + len2 + 1);
  memcpy(result, s1, len1);
  memcpy(result + len1, s2, len2 + 1);
  return result;
}

void _mkdir(const char *name)
{
  struct stat st = {0};
  if (stat(name, &st) == -1) {
    mkdir(name, 0700);
  }
}

void generate_sug_files()
{
  FILE *f;
  unsigned long i;
  static char *ws = " \f\t\v";
  static char *al = "abcdefghijklmnoprstuvwxyz";
  static char *i5 = "a b c d e f g h i j k l m "
                    "n o p q r s t u v w x y z "
                    "a b c d e f g h i j k l m "
                    "n o p q r s t u v w x y z "
                    "a b c d e f g h i j k l m "
                    "n\n";
  /* Generate the following: */
  /* 0. input file contains zero words */
  f = fopen(strlitconcat(TEST_DIR, "test_0"), "w");
  assert(f != NULL);
  fclose(f);

  /* 1. input file contains 1 enormous word without any newlines */
  f = fopen(strlitconcat(TEST_DIR, "test_1"), "w");
  assert(f != NULL);
  for (i = 0; i < ((66000ul / 26) + 1); i++)
    fputs(al, f);
  fclose(f);

  /* 2. input file contains all white space without newlines */
  f = fopen(strlitconcat(TEST_DIR, "test_2"), "w");
  assert(f != NULL);
  for (i = 0; i < ((66000ul / 4) + 1); i++)
    fputs(ws, f);
  fclose(f);

  /* 3. input file contains 66000 newlines */
  f = fopen(strlitconcat(TEST_DIR, "test_3"), "w");
  assert(f != NULL);
  for (i = 0; i < 66000; i++)
    fputc('\n', f);
  fclose(f);

  /* 4. input file contains word/
   *    {huge sequence of whitespace of different kinds}
   *    /word
   */
  f = fopen(strlitconcat(TEST_DIR, "test_4"), "w");
  assert(f != NULL);
  fputs("word", f);
  for (i = 0; i < ((66000ul / 26) + 1); i++)
    fputs(ws, f);
  fputs("word", f);
  fclose(f);

  /* 5. input file contains 66000 single letter words,
   *    66 to the line
   */
  f = fopen(strlitconcat(TEST_DIR, "test_5"), "w");
  assert(f != NULL);
  for (i = 0; i < 1000; i++)
    fputs(i5, f);
  fclose(f);

  /* 6. input file contains 66000 words without any newlines */
  f = fopen(strlitconcat(TEST_DIR, "test_6"), "w");
  assert(f != NULL);
  for (i = 0; i < 66000; i++)
    fputs("word ", f);
  fclose(f);

}

int wc(FILE *f)
{
  int c, _wc = 0;
  while ((c = getc(f)) != EOF) {
    if ((c == ' ' || c == '\n') && !isspace(getc(f)))
      _wc++;
  }
  return _wc;
}

void map_files_in_dir(const char *dir, int (*map_func)(FILE *f))
{
  DIR *dp;
  struct dirent *ep;

  dp = opendir (dir);
  if (dp != NULL)
  {
    while (ep = readdir (dp)) {
      const char *f_name = ep->d_name;
      if (strcmp(f_name, ".") && strcmp(f_name, "..")) {
        char *full_f_name = concat(TEST_DIR, f_name);
        FILE *f = fopen(full_f_name, "r");
        printf("%s wc:%d\n", f_name, map_func(f));
        fclose(f); free(full_f_name);
      }
    }
    (void) closedir (dp);
  }
  else
    perror ("Couldn't open the directory");
}

int main()
{
  _mkdir(TEST_DIR);
  generate_sug_files();
  map_files_in_dir(TEST_DIR, wc);
  return 0;
}
