
#include "mystddef.h"

void *mymalloc(size_t size);
void myfree(void *ptr);

void *mycalloc(size_t nmemb, size_t size);
void *myrealloc(void *ptr, size_t size);

int mystrtoint(const char *input, int *result);
char *myinttostr(char *output, int value);