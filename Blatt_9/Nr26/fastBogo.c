#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int *numbers;

typedef struct {
	int from;
	int to;
} range;

int isSorted(int from, int to) {
	for (int i = from; i < to - 1; i++) {
		if (numbers[i] > numbers[i + 1]) {
			return 0;
		}
	}
	return 1;
}

void* bogo(void* arg) {
	int start = *((int*) arg);
	int end = start + 4;
	printf("thread started with start=%i end=%i\n", start, end);
	while (!isSorted(start, end)) {
		int a = start + rand() % 4;
		int b = start + rand() % 4;

		//swap
		int temp = numbers[a];
		numbers[a] = numbers[b];
		numbers[b] = temp;
	}
	
	return (void*) 0;
}

void* join(void* arg) {
	range *r = (range*) arg;
	printf("join thread started with start=%i end=%i\n", r->from, r->to);
	int len = r->to - r->from;
	int copy[len];
	for (int i = 0; i < len; i++) {
		copy[i] = numbers[r->from + i];
	}
	int i = 0;
	int j = len / 2;
	int index = r->from;
	while (i < len / 2 && j < len) {
		if (copy[i] <= copy[j]) {
			numbers[index] = copy[i];
			i++;
		} else {
			numbers[index] = copy[j];
			j++;
		}
		index++;
	}
	while (i < len / 2) {
		numbers[index] = copy[i];
		i++;
		index++;
	}
	while (j < len) {
		numbers[index] = copy[j];
		j++;
		index++;
	}
	return (void*) 0;
}

int main(int argc, char const *argv[]) {
	if (argc < 2) return -1;
	int n = atoi(argv[1]);
	long elements = pow(2, n);

	srand(time(NULL)); //init random

	//init numbers
	numbers = malloc(elements * sizeof(int));
	if (numbers == NULL) {
		puts("malloc failed");
		return - 1;
	}
	for (size_t i = 0; i < elements; i++) {
		numbers[i] = rand() % 10001;
	}

	//launch threads
	int threadNum = elements / 4;
	pthread_t threads[threadNum];
	int args[threadNum];
	for (int i = 0; i < threadNum; i++) {
		args[i] = i * 4;
		pthread_create(&threads[i], NULL, bogo, &args[i]);
	}
	
	for (int i = 0; i < threadNum; i++) {
		pthread_t t = threads[i];
		pthread_join(t, NULL);
	}
	range argJoin[threadNum / 2];
	for (int tNum = threadNum / 2; tNum >= 1; tNum /= 2) {
		for (int i = 0; i < tNum; i++) {
			argJoin[i].from = i * (elements / tNum);
			argJoin[i].to = argJoin[i].from + (elements / tNum);
			pthread_create(&threads[i], NULL, join, &argJoin[i]);
		}
		
		for (int i = 0; i < tNum; i++) {
			pthread_t t = threads[i];
			pthread_join(t, NULL);
		}
	}
	
	putchar('[');
	for (long i = 0; i < elements; i++) {
		printf("%i, ", numbers[i]);
	}
	puts("]");
	return 0;
}