#include "shell.h"
#include "mygetline.h"
#include <stdio.h>
#include "mystdlib.h"

int main(int argc, char const *argv[]) {
	
	char *buf = mymalloc(1);
	if (buf == NULL) return -1;
	size_t buflen = 1;
	ssize_t lines = mygetline(&buf, &buflen, 0);
	if (lines == -1) {
		puts("error while reading stdin");
		return 1;
	}
	//puts(buf);
	char **splited = shell_split(buf);
	if (splited == NULL) {
		puts("error while splitting");
		return -1;
	}

	for (size_t i = 0; splited[i] != NULL; i++) {
		printf("%lu: %s\n", i, splited[i]);
		myfree(splited[i]);
	}
	myfree(splited);
	myfree(buf);
	return 0;
}
