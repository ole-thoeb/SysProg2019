#include "mygetline.h"
#include "myunistd.h"
#include "mystdlib.h"

size_t increaseBuffer(void **buf, size_t *buflen, size_t size) {
	size_t len = *buflen;
	if (*buflen == 0) len = size;
	len *= 2;

	*buf = myrealloc(*buf, len);
	if (*buf == NULL) {
		//puts("could reallocate buf");
		return -1;
	}
	*buflen = len;
	return 0;
}

ssize_t mygetline(char **buf, size_t *buflen, int fd) {

	ssize_t curlen = 0;
	while (1) {
		// if buffer is too short: double length and abort if malloc fails
		if (curlen + 1 >= *buflen && increaseBuffer(buf, buflen, sizeof(char)) == -1) {
			return -1;
		}
		ssize_t res = myread(fd, *buf + curlen, 1);
		if (res < 0) return -1;
		if (res == 0) {
			(*buf)[curlen] = '\0';
			return curlen;
		}
		if ((*buf)[curlen] == '\n') {
			(*buf)[curlen + 1] = '\0';
			return curlen;
		}
		curlen++;
	}
}