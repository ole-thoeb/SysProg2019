
SRC = palindrom_errors.c
OBJECTS = palindrom_errors.o
HEADERS = 
BIN = palindrom_errors

CC = clang
CFLAGS = -g -Wall -Wextra -fsanitize=address
LDFLAGS = -g -Wall -Wextra -fsanitize=address

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BIN): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS)

.PHONY: clean
clean:
	rm -rf $(BIN) $(OBJECTS)