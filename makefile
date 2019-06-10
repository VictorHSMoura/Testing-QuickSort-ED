trabalho: main.o stack.o sorting.o
	gcc -O3 main.o stack.o sorting.o -o trab.exe
	make clean
	clear

main.o: src/main.c
	gcc -O3 -c src/main.c

sorting.o: src/sorting.c src/headers/sorting.h
	gcc -O3 -c src/sorting.c

stack.o: src/stack.c src/headers/stack.h
	gcc -O3 -c src/stack.c

clean:
	rm *.o
