
SRC = fastBogo.c
OBJECTS = fastBogo.o
HEADERS = 
BIN = fastBogo.out

CC = clang
CFLAGS = -g -pthreads -Wall -fsanitize=address
LDFLAGS = -g -pthreads -Wall -lm -fsanitize=address

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BIN): $(SRC)
	$(CC) $(LDFLAGS) -o $@ $(SRC)

.PHONY: clean
clean:
	rm -rf $(BIN) $(OBJECTS)