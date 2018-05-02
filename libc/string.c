#include "string.h"
#include <stdint.h>


void int_to_ascii(int n, char str[]) {
    int i, sign;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';

    reverse(str);
}

void hex_to_ascii(int n, char str[]) {
    append(str, '0');
    append(str, 'x');
    char zeros = 0;

    int32_t tmp;
    int i;
    for (i = 28; i > 0; i -= 4) {
        tmp = (n >> i) & 0xF;
        if (tmp == 0 && zeros == 0) continue;
        zeros = 1;
        if (tmp > 0xA) append(str, tmp - 0xA + 'a');
        else append(str, tmp + '0');
    }

    tmp = n & 0xF;
    if (tmp >= 0xA) append(str, tmp - 0xA + 'a');
    else append(str, tmp + '0');
}


void reverse(char s[]) {
    int c, i, j;
    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}


int strlen(char s[]) {
    int i = 0;
    while (s[i] != '\0') ++i;
    return i;
}

void append(char s[], char n) {
    int len = strlen(s);
    s[len] = n;
    s[len+1] = '\0';
}

void backspace(char s[]) {
    int len = strlen(s);
    s[len-1] = '\0';
}

int strcmp(char s1[], char s2[]) {
    int i;
    to_lower(s1); 
    to_lower(s2);
    for (i = 0; s1[i] == s2[i]; i++) {
        if (s1[i] == '\0') return 0;
    }
    return s1[i] - s2[i];
}

int strstw(char s1[], char s2[]) {
    int i;
    int len = strlen(s2);
    to_lower(s1); 
    to_lower(s2);    
    for (i = 0; s1[i] == s2[i]; i++) {
        if (s2[i+1] == '\0') 
        return 0;
    }
    return s1[i] - s2[i];
}

char* substr(char* s, int p1, int p2){
    char* temp = "";
    int substrcounter = 0;
    int i = p1;
    for (i ; i<p2;i++){
        temp[substrcounter] = s[i];
        substrcounter++;
    }
    temp[substrcounter] = '\0';
    return temp;
}

void to_lower(char* s) {
    int i = 0;
	for (i; i < strlen(s); i++)
		if (s[i] >= 'A' && s[i] <= 'Z')
			s[i] = s[i] | (1 << 5);
}
 
void to_upper(char* s) {
    int i = 0;    
	for (i; i < strlen(s); i++)
		if (s[i] >= 'a' && s[i] <= 'z')
			s[i] = s[i] & (~(1<<5));
}