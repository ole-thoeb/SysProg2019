
SRC = mystdlib.c strinttest.c
OBJECTS = mystdlib.o strinttest.o
HEADERS = mystdlib.h mystddef.h
BIN = strinttest.out

CC = clang
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

.PHONY: all
all:
	$(CC) $(LDFLAGS) -o $(BIN) $(SRC)