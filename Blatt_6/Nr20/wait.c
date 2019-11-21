#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char const *argv[]) {
	if (argc < 2) return 1;
	int wait = atoi(argv[1]);
	int limit = atoi(argv[2]);
	long i = 0;
	struct timespec tspec;
	tspec.tv_sec = 0;
	tspec.tv_nsec = wait;

	struct timespec startTime;
	struct timespec endtime;
	while (1) {
		clock_gettime(CLOCK_MONOTONIC, &startTime);
		if (nanosleep(&tspec, NULL)  < 0) {
			printf("Nano sleep system call failed \n");
			return -1;
		}
		clock_gettime(CLOCK_MONOTONIC, &endtime);
		if (endtime.tv_nsec - startTime.tv_nsec > limit) {
			printf("slept %li ns. in iterations %ld\n", endtime.tv_nsec - startTime.tv_nsec, i);
			i = 0;
		} else {
			i++;
		}
	}
	
	return 0;
}