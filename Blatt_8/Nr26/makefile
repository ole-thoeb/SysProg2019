
SRC = dotproduct.c
OBJECTS = dotproduct.c
HEADERS = 
BIN = dotprod.out

CC = clang
CFLAGS = -g -pthreads -Wall -fsanitize=address
LDFLAGS = -g -pthreads -Wall -fsanitize=address

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BIN): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS)

.PHONY: clean
clean:
	rm -rf $(BIN) $(OBJECTS)