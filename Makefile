install:
	gcc assembler.c -o assembler -fsanitize=address
	gcc Stack/Stack.c -c -o Stack.o -fsanitize=address
	gcc spu.c -o spu Stack.o -fsanitize=address

clean:
	rm Stack.o