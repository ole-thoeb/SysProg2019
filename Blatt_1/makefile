SRC = mystring.c mystringTest.c
OBJECTS = mystring.o mystringTest.o
HEADERS = mystring.h mystddef.h

CFLAGS = -g -Wall -fsanitize=address
LDFLAGS = -g -Wall -fsanitize=address

%.o: %.c $(HEADERS)
	clang $(CFLAGS) -c -o $@ $<

blatt_1: $(OBJECTS)
	clang $(LDFLAGS) -o $@ $(OBJECTS)