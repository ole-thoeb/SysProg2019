#include <stdio.h>
#include <stdlib.h>
#include<time.h>

int main(int argc, char const *argv[]) {
	if (argc != 3) return 1;

	srand(time(0));

	int x = atoi(argv[1]);
	int y = atoi(argv[2]);

	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			printf("%i", (rand() % 200) - 100);
			if (j < y - 1) {
				putchar(',');
			}
		}
		if (i < x - 1) {
				putchar(';');
		}
	}

	return 0;
}
