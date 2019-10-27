#include <stdio.h>
#include <stdlib.h>
#include <string.h> // <- missing header
#include <ctype.h> // <- missing header

int palindrom_check1(const char *st1) {
	int st1_len = strlen(st1), i;

	for(i = 0; i < st1_len / 2; i++)
		if (toupper(st1[i]) != toupper(st1[st1_len - i - 1])) return 0; // <- CHANGED st1_len -1

	return 1;
}

int main(void) {
	char *st1, *st2;
	int st1_len, i;
	char *exit = "exit"; // <- CHANGED ' to "

	st1 = malloc(100);
	st2 = malloc(100);

	printf("Zum Beenden exit als Eingabe angeben. \n");
	while (1) {
		printf("Eingabe: ");
		scanf("%s", st1);
		if (strcmp(st1, exit) == 0) break; // <- CHANGED return to break

		st1_len = strlen(st1);

		for (i = 0; i < st1_len; i++) {
			st2[i] = toupper(st1[st1_len - 1 - i]);
			st1[i] = toupper(st1[i]); // <- INSERTED also upper st1
		}
		st2[st1_len] = '\0'; // <- INSERTED missing null termination of st2
    
		if (palindrom_check1(st1)) printf("1. Test: Palindrom\n"); // <- REMOVED bad space
		else printf("1. Test: Kein Palindrom\n"); // <- REMOVE bad space
 
		if (strcmp(st1, st2) == 0) printf("2. Test: Palindrom\n"); // <- FIXED wrong compare of strings
		else printf("2. Test: Kein Palindrom\n");
	}
	
	free(st1); // <- INSERTED missing free
	free(st2); // <- INSERTED missing free
	return 0;
}