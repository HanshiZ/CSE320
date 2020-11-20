decoder: main.o stack.o node.o
	gcc -o decoder main.o stack.o node.o
main.o: main.c
	gcc -c -Wall main.c
stack.o: stack.c stack.h
	gcc -c -Wall stack.c
node.o: node.c node.h
	gcc -c -Wall node.c

