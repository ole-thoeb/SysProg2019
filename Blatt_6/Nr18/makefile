
SRC = shell.c shellTest.c mygetline.c
OBJECTS = shell.o shellTest.o mygetline.o
LIB =  library.a
HEADERS = mystddef.h mystdlib.h mygetline.h shell.h myunistd.h
BIN = shelltest.out

CC = clang
AC = nasm
CFLAGS = -g -Wall -fsanitize=address
LDFLAGS = -g -Wall -fsanitize=address

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.asm
	$(AC) -felf64 -o $@ $<

$(BIN): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS) $(LIB)

.PHONY: clean
clean:
	rm -rf $(BIN) $(OBJECTS)

.PHONY: all
all:
	$(CC) $(LDFLAGS) -o $(BIN) $(SRC) $(LIB)