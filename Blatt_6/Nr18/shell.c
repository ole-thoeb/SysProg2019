#include "shell.h"
#include "mystddef.h"
#include "mystdlib.h"
#include "mygetline.h"

char *emptychars = "\t\n\v\f\r ";
int emptycharlen = 6;


char **shell_split(char *input) {
	size_t b = 0; //index were we add next string to result array
	size_t bufLen = 0;
	char **buf = NULL;

	size_t i = 0; //pos of char we read next
	Top_Level_Loop: while (1) {
		size_t s = 0; //length of string we are building
		size_t stringBufLen = 0;
		char *stringBuf = NULL;

		// if buffer is too short: double length and abort if malloc fails
		if (b + 1 >= bufLen && increaseBuffer(&buf, &bufLen, sizeof(char*)) == -1) {
			return NULL;
		}

		while (1) {
			// if buffer is too short: double length and abort if malloc fails
			if (s >= stringBufLen && increaseBuffer(&stringBuf, &stringBufLen, sizeof(char)) == -1) {
				return NULL;
			}
			if (input[i] == '\0') {
				//null terminate string
				stringBuf[s] = '\0';
				buf[b] = stringBuf;
				b++;
				//null terminate list
				buf[b] = NULL;
				return buf;
			}
			for (int e = 0; e < emptycharlen; e++) {
				if (input[i] == emptychars[e]) {
					if (s != 0) { //if we dont have an empty string
						//null terminate string
						stringBuf[s] = '\0';
						buf[b] = stringBuf;
						b++;
					}
					i++;
					goto Top_Level_Loop;
				}
			}
			stringBuf[s] = input[i];
			s++;
			i++;
		}
		i++;
	}
	
}