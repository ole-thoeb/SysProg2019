
SRC = launcher.c
OBJECTS = launcher.o
HEADERS = 
BIN = launcher.out

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
