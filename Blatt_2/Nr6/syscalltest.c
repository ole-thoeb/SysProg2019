#include "mystddef.h"
#include "myunistd.h"

int main(int argc, char const *argv[]) {
	
	mywrite(0, "abc\n", 4);
	myexit(1);
	mywrite(0, "nothing\n", 8);

	return 0;
}
