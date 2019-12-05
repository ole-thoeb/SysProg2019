#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
//#include <process.h>

int main(int argc, char const *argv[]) {
	if (argc < 3) {
		fprintf(stderr, "to few arguments");
		exit(-1);
	}

	int times = atoi(argv[1]);
	const char *programm = argv[2];
	
	for (int i = 0; i < times; i++) {		
		pid_t pid = fork();
		if (pid < 0) {
			fprintf(stderr, "fork failed");
			exit(-1);
		} else if (pid == 0) { //child
			execvp(programm, argv + 2);
		} else { //parent
			//nothing
		}
	}
	while (wait(NULL) > 0) {
		//puts("n");
	}

	return 0;
}
