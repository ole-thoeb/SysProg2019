#include "shell.h"
#include "mygetline.h"
#include <stdio.h>

int main(int argc, char const *argv[]) {
	
	char *buf;
	size_t buflen = 0;
	ssize_t lines = mygetline(&buf, &buflen, 0);
	if (lines == -1) {
		puts("error while reading stdin");
		return 1;
	}
	puts(buf);
	char **splited = shell_split(buf);
	if (splited == NULL) {
		puts("error while splitting");
		return 1;
	}

	for (size_t i = 0; splited[i] != NULL; i++) {
		puts(splited[i]);
	}
	return 0;
}
