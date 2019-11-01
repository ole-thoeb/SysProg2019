
SRC = mystdlib.c mallocTest.c
OBJECTS = mystdlib.o mallocTest.o
HEADERS = mystddef.h mystdlib.h
BIN = mallocTest

CC = clang
AC = nasm
CFLAGS = -g -Wall -fsanitize=address
LDFLAGS = -g -Wall -fsanitize=address

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.asm
	$(AC) -felf64 -o $@ $<

$(BIN): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS)

.PHONY: clean
clean:
	rm -rf $(BIN) $(OBJECTS)