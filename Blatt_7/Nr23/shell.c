#include "shell.h"
#include "mystddef.h"
#include "mystdlib.h"
#include "mygetline.h"
#include "myunistd.h"
#include "mystring.h"

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
		if (b + 1 >= bufLen && increaseBuffer((void**)&buf, &bufLen, sizeof(char*)) == -1) {
			return NULL;
		}

		while (1) {
			// if buffer is too short: double length and abort if malloc fails
			if (s >= stringBufLen && increaseBuffer((void**)&stringBuf, &stringBufLen, sizeof(char)) == -1) {
				return NULL;
			}
			if (input[i] == '\0') {
				if (s != 0) {
					//null terminate string
					stringBuf[s] = '\0';
					buf[b] = stringBuf;
					b++;
				} else {
					myfree(stringBuf);
				}
				
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
					} else {
						myfree(stringBuf);
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

extern char **environ;

pid_t run_command(char **argv, int no_fork) {
	char *cmd = argv[0];

	if (!no_fork) {
		pid_t pid = myfork();
		if (pid < 0) { //error
			mywrite(2, "forkfailed\n", 11);
			return pid;
		} else if (pid == 0) { //child
			int result = myexecve(cmd, argv, environ); //should not return
			mywrite(2, "execfailed\n", 11);
			return result;
		} else { //parent
			return pid;
		}
	}
	return -1;
}

int run_cmdline(char **argv) {
	pid_t pid = run_command(argv, 0);
	if (pid > 0) {
		pid_t finishedProcess = mywait4(pid, NULL, 0, NULL);
		if (finishedProcess < 0) return finishedProcess; //error occurred
		return 0;
	} else {
		return pid;
	}
}

int stderr = 2;
int stdin = 0;

int handlerError(ssize_t errorCode, char *context) {
	mywrite(stderr, "an error occurred! CODE:", 24);

	char *buf = mymalloc(15);
	if (!buf) return -1;

	char *errorString = myinttostr(buf, errorCode);
	mywrite(stderr, errorString, mystrlen(errorString));
	myfree(buf);

	mywrite(stderr, " ", 1);
	mywrite(stderr, context, mystrlen(context));
	mywrite(stderr, "\n", 1);
	return 0;
}

int main(int argc, char const *argv[]) {
	ssize_t retCode;
	size_t bufSize = 512;
	char *readLineBuf = mymalloc(bufSize);
	if (readLineBuf == NULL) return -1;

	while (1) {
		if ((retCode = mywrite(stderr, "$ ", 2)) < 0) {
			handlerError(retCode, "while writing");
			continue;
		}
		retCode = mygetline(&readLineBuf, &bufSize, stdin);
		if (retCode == 0) break;
		if (retCode < 0) {
			handlerError(retCode, "reading line failed");
			continue;
		}
		char **args = shell_split(readLineBuf);
		if (args == NULL) {
			handlerError(-1, "spliting failed");
			continue;
		}
		if (args[0] == NULL) continue;
		if ((retCode = run_cmdline(args)) < 0) {
			handlerError(retCode, "could not execute comand");
			continue;
		}
	}
	myfree(readLineBuf);
	return 0;
}
