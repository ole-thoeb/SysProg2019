
SRC = rwlock.c rwtest.c
OBJECTS = rwlock.o rwtest.o
HEADERS = rwlock.h
BIN = rwlock.out

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