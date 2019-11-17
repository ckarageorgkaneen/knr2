/* Write a function escape(s,t) that converts characters like newline and tab into visible escape sequences like \n and \t as it copies the string t to s . Use a switch . Write a function for the other direction as well, converting escape sequences into the real characters. */
#include <stdio.h>
#include <string.h>
#include <assert.h>
#define BUFFER_SIZE 100

void escape(char*, char*);
void unescape(char*, char*);

int main(void)
{
	char text1[BUFFER_SIZE] = "\aHello,\n\tWorld! Mistakee\b was \"Extra 'e'\"!\n";
	char text2[BUFFER_SIZE];

	escape(text2, text1);
	assert(strcmp(text2,
	              "\\aHello,\\n\\tWorld! Mistakee\\b was \\\"Extra 'e'\\\"!\\n")
	       == 0);
	unescape(text1, text2);
	assert(strcmp(text1,
	              "\aHello,\n\tWorld! Mistakee\b was \"Extra 'e'\"!\n")
	       == 0);

	return 0;
}

void escape(char* s, char* t)
{
	int i, j;
	i = j = 0;
	while ( t[i] ) {
		switch ( t[i] ) {
		case '\n':
			s[j++] = '\\';
			s[j] = 'n';
			break;

		case '\t':
			s[j++] = '\\';
			s[j] = 't';
			break;

		case '\a':
			s[j++] = '\\';
			s[j] = 'a';
			break;

		case '\b':
			s[j++] = '\\';
			s[j] = 'b';
			break;

		case '\f':
			s[j++] = '\\';
			s[j] = 'f';
			break;

		case '\r':
			s[j++] = '\\';
			s[j] = 'r';
			break;

		case '\v':
			s[j++] = '\\';
			s[j] = 'v';
			break;

		case '\\':
			s[j++] = '\\';
			s[j] = '\\';
			break;

		case '\"':
			s[j++] = '\\';
			s[j] = '\"';
			break;

		default:
			s[j] = t[i];
			break;
		}
		i++;
		j++;
	}
	s[j] = t[i];
}

void unescape(char* s, char* t)
{
	int i, j;
	i = j = 0;

	while ( t[i] ) {
		switch ( t[i] ) {
		case '\\':
			switch ( t[++i] ) {
			case 'n':
				s[j] = '\n';
				break;

			case 't':
				s[j] = '\t';
				break;

			case 'a':
				s[j] = '\a';
				break;

			case 'b':
				s[j] = '\b';
				break;

			case 'f':
				s[j] = '\f';
				break;

			case 'r':
				s[j] = '\r';
				break;

			case 'v':
				s[j] = '\v';
				break;

			case '\\':
				s[j] = '\\';
				break;

			case '\"':
				s[j] = '\"';
				break;

			default:
				s[j++] = '\\';
				s[j] = t[i];
			}
			break;

		default:
			s[j] = t[i];
		}
		++i;
		++j;
	}
	s[j] = t[i];
}