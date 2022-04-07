install:
	gcc Stack/Stack.c -c -o Stack.o -fsanitize=address
	gcc LMap/LMap.c -c -o LMap.o -fsanitize=address
	gcc spu.c -o spu Stack.o -fsanitize=address
	gcc asm.c -o asm LMap.o -fsanitize=address

clean:
	rm Stack.o || true
	rm LMap.o || true
