#include "mystddef.h"
#include "mystring.h"
#include <stdio.h>

size_t mystrlen(char *str) {
	size_t len = 0;
	while (str[len] != '\0') {
		len++;
	}
	return len;
}

char *mystrcpy(char *dest, const char *src) {
	dest[0] = src[0];
	for (size_t i = 1; src[i - 1] != '\0'; i++) {
		dest[i] = src[i];
	}
	return dest;
}

char *mystrcat(char *dest, const char *src) {
	size_t i = 0;
	while (dest[i] != '\0') {
		i++;
	}
	mystrcpy(dest + (i * sizeof(char)), src);
	return dest;
}

int charcmp(char c1, char c2) {
	printf("%c to %c\n", c1, c2);
	return c1 - c2;
}

int mystrcmp(const char *s1, const char *s2) {
	size_t i = 0;
	while (s1[i] != '\0' || s2[i] != '\0') {
		int charResult = charcmp(s1[i], s2[i]);
		if (charResult != 0){
			return charResult;
		}
		i++;
	}
	if (s1[i] == '\0') {
		if (s2[i] == '\0'){
			return 0;
		} else {
			//s1 is shorter than s2
			return -1;
		}
	} else {
		//s1 is longer than s2
		return 1;
	}
}


void *mymemcpy(void *dest, const void *src, size_t n) {
	for (size_t i = 0; i < n; i++) {
		//long offset = i * 8;
		((char*)dest)[i] = ((char*)src)[i];
	}
	return dest;
}

void *mymemset(void *buf, int ch, size_t n) {
	for (size_t i = 0; i < n; i++) {
		((char*)buf)[i] = ch;
	}
	return buf;
}
