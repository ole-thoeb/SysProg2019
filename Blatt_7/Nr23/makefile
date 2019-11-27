
SRC = mystdlib.c myunistd.s shell.c mygetline.c mystring.c
OBJECTS = mystdlib.o myunistd.o shell.o mygetline.o mystring.o
HEADERS = mystdlib.h mystddef.h mygetline.h shell.h myunistd.h mystring.h
BIN = shell.out

CC = clang
AC = nasm
CFLAGS = -g -Wall -fsanitize=address
LDFLAGS = -g -Wall -fsanitize=address

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.s
	$(AC) -felf64 -o $@ $<

$(BIN): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS)

.PHONY: clean
clean:
	rm -rf $(BIN) $(OBJECTS)

.PHONY: all
all:
	$(CC) $(LDFLAGS) -o $(BIN) $(SRC)