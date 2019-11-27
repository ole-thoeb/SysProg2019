SRC = glib.asm main.c
OBJECTS = glib.o main.o
BIN = glib.out

AC = nasm
CC = clang

%.o: %.asm
	$(AC) -f elf64 -o $@ $<

%.o: %.c 
	$(CC) -c -o $@ $<

$(BIN): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS)

.PHONY: clean
clean:
	rm -rf $(BIN) $(OBJECTS)