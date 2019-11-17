/* Expand dcl to handle declarations with function argument types, qualifiers like const , and so on. */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
#define MAXOUT 1000
enum {
    NAME, PARENS, BRACKETS, ERROR
};
enum { NO, YES };

void dcl(void);
void dirdcl(void);

int gettoken(void);
int tokentype;
int prevtoken;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[MAXOUT];

int main()
{
    while (gettoken() != EOF) {
        strcpy(datatype, token);
        out[0] = '\0';
        dcl();
        if (tokentype != '\n') {
            fprintf(stderr, "syntax error: %c\n", tokentype);
            while (gettoken() != '\n')
                ;
        } else
            printf("%s %s %s\n", name, out, datatype);
    }
    return 0;
}

void dcl(void)
{
    int ns;

    for (ns = 0; gettoken() == '*';)
        ns++;
    dirdcl();
    while (ns-- > 0)
        strcat(out, " pointer to");
}

void dirdcl(void)
{
    int type;
    void parmdecl(void);

    if (tokentype == '(') {
        dcl();
        if (tokentype != ')') {
            printf("error: missing )\n");
            prevtoken = YES;
        }
    } else if (tokentype == NAME)
        strcpy(name, token);
    else
        prevtoken = YES;

    while ((type = gettoken()) == PARENS || type == BRACKETS || type == '(')
        if (type == PARENS)
            strcat(out, " function returning");
        else if (type == '(') {
            strcat(out, " function expecting");
            parmdecl();
            strcat(out, " and returning");
        } else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
}

void parmdecl(void)
{
    void declspec(void);

    do {
        declspec();
    } while (tokentype == ',');
    if (tokentype != ')') {
        prevtoken = YES;
        printf("missing ) in parameter declaration\n");
    }
}

void declspec(void)
{
    int typespec(void);
    int typequal(void);

    char temp[MAXTOKEN];

    temp[0] = '\0';
    gettoken();
    do {
        if (tokentype != NAME) {
            prevtoken = YES;
            dcl();
        }
        else if (typespec() == YES) {
            strcat(temp, " ");
            strcat(temp, token);
            gettoken();
        }
        else if (typequal() == YES) {
            strcat(temp, " ");
            strcat(temp, token);
            gettoken();
        }
        else {
            prevtoken = YES;
            printf("unknown type in parameter list\n");
        }
    } while (tokentype != ',' && tokentype != ')');
    strcat(out, temp);
    if (tokentype == ',')
        strcat(out, ",");
}

int typespec(void)
{
    static char *types[] = {
        "char",
        "double",
        "float",
        "int",
        "long",
        "short",
        "void"
    };

    char *p = token;
    char **cp = types;

    for (;; cp++)
        if (strcmp(*cp, p))
            return YES;
    return NO;
}

int typequal(void)
{
    static char *typeq[] = {
        "const",
        "volatile"
    };

    char *p = token;
    char **cp = typeq;
    for (;; cp++)
        if (strcmp(*cp, p))
            return YES;

    return NO;
}

int gettoken(void)
{
    int c, getch(void);
    void ungetch(int);
    char *p = token;

    if (prevtoken == YES) {
        prevtoken = NO;
        return tokentype;
    }

    while ((c = getch()) == ' ' || c == '\t')
        ;
    if (c == '(') {

        // consume blanks after opening parenthesis
        while ((c = getch()) == ' ' || c == '\t')
            ;

        if (c == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetch(c);
            return tokentype = '(';
        }
    } else if (c == '[') {

        // consume blanks after opening bracket
        while ((c = getch()) == ' ' || c == '\t')
            ;
        ungetch(c);

        for (*p++ = '['; (*p++ = getch()) != ']';)
            ;
        *p = '\0';
        return tokentype = BRACKETS;
    } else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getch());)
            *p++ = c;
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    } else
        return tokentype = c;
}

int is_valid_datatype(char *datatype)
{
    return strcmp(datatype, "char") == 0 ||
           strcmp(datatype, "short") == 0 ||
           strcmp(datatype, "int") == 0 ||
           strcmp(datatype, "long") == 0 ||
           strcmp(datatype, "float") == 0 ||
           strcmp(datatype, "double") == 0 ||
           strcmp(datatype, "void") == 0;
}


#define BUFSIZE 100

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

int getch(void) /* get a (possibly pushed back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
