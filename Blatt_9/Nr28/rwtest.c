#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "rwlock.h"


struct rwlock lock;

void* rThread(void *arg) {
	char *name = (char*) arg;
	printf("thread %s says hello\n", name);
	rwlock_lock_read(&lock);
	for (int i = 0; i < 3; i++) {
		sleep(1);
		printf("%s: reading...\n", name);
	}
	rwlock_unlock_read(&lock);
	return (void *) 0;
}

void* wThread(void *arg) {
	char *name = (char*) arg;
	printf("thread %s says hello\n", name);
	rwlock_lock_write(&lock);
	for (int i = 0; i < 3; i++) {
		sleep(1);
		printf("%s: writing...\n", name);
	}
	rwlock_unlock_write(&lock);
	return (void *) 0;
}

int main(int argc, char const *argv[]) {
	rwlock_init(&lock);
	pthread_t w1;
	pthread_create(&w1, NULL, wThread, "w1");
	pthread_t w2;
	pthread_create(&w2, NULL, wThread, "w2");
	pthread_t r1;
	pthread_create(&r1, NULL, rThread, "r1");
	pthread_join(w1, NULL);
	pthread_join(w2, NULL);
	pthread_join(r1, NULL);

	pthread_t r2;
	pthread_create(&r2, NULL, rThread, "r2");
	pthread_t w3;
	pthread_create(&w3, NULL, wThread, "w3");
	pthread_t r3;
	pthread_create(&r3, NULL, rThread, "r3");
	pthread_join(w3, NULL);
	pthread_join(r2, NULL);
	pthread_join(r3, NULL);
	
	pthread_t w4;
	pthread_create(&w4, NULL, wThread, "w4");
	pthread_t r4;
	pthread_create(&r4, NULL, rThread, "r4");
	pthread_t w5;
	pthread_create(&w5, NULL, wThread, "w5");
	pthread_join(w4, NULL);
	pthread_join(r4, NULL);
	pthread_join(w5, NULL);
	return 0;
}
