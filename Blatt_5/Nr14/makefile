SRC = m_add.asm matrix.c
OBJECTS = m_add.o matrix.o
BIN = matrix.out

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