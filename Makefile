install:
	gcc Stack/Stack.c -c -o Stack.o -fsanitize=address
	gcc LMap/LMap.c -c -o LMap.o -fsanitize=address
	gcc spu.c -o spu Stack.o -fsanitize=address
	gcc assembler.c -o assembler LMap.o -fsanitize=address

clean:
	rm Stack.o
	rm LMap.o
