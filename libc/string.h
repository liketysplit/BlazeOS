#ifndef STRINGS_H
#define STRINGS_H

void int_to_ascii(int n, char str[]);
void hex_to_ascii(int n, char str[]);
void reverse(char s[]);
int strlen(char s[]);
void backspace(char s[]);
void append(char s[], char n);
int strcmp(char s1[], char s2[]);
int strstw(char s1[], char s2[]);
char* substr(char* s, int p1, int p2);
void to_lower(char* s);
void to_upper(char* s);

#endif
