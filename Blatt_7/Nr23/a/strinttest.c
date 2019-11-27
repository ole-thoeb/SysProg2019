#include "mystdlib.h"
#include "stdio.h"

int main(int argc, char const *argv[]) {
	int res;
	printf("read %i symbols\n", mystrtoint("-547", &res));
	printf("%i\n", res);
	char *buf = mymalloc(10);
	printf("%s\n", myinttostr(buf, -6547));
	myfree(buf);
	return 0;
}
