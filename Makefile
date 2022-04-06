install:
	gcc assembler.c -o assembler -fsanitize=address

clean:
	rm assembler || true