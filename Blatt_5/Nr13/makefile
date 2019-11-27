SRC = fibonacci-stub.asm
OBJECTS = fibonacci-stub.o
BIN = fibonacci.out

AC = nasm

%.o: %.asm
	$(AC) -f elf64 -o $@ $<

$(BIN): $(OBJECTS)
	ld $< -o $@

.PHONY: clean
clean:
	rm -rf $(BIN) $(OBJECTS)