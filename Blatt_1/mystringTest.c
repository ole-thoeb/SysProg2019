#include "mystring.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
	char s[] = "abcd";
	printf("%lu\n", mystrlen(s));

	char dest[40];
	mystrcpy(dest, s);
	mystrcat(dest, s);
	printf("%s\n", dest);

	char s2[] = "abCd";
	printf("%s ist größer\n", mystrcmp(s, s2) > 0 ? "s2" : "s1");

	void *buf = malloc(8 * 64);
	mymemset(buf, 42, 8);
	void *result = malloc(8 * 64);
	mymemset(result, 0, 64);
	mymemcpy(result, buf, 8);
	printf("%s\n", result);

	free(buf);
	free(result);
	return 0;
}
