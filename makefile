trabalho: main.o stack.o sorting.o
	gcc main.o stack.o sorting.o -o trab.exe
	make clean
	clear

main.o: src/main.c
	gcc -c src/main.c

sorting.o: src/sorting.c src/headers/sorting.h
	gcc -c src/sorting.c

stack.o: src/stack.c src/headers/stack.h
	gcc -c src/stack.c

clean:
	rm *.o