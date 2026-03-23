CC = gcc -g

pgm_tools: main.o menu.o pgm_tools.o
	gcc main.o menu.o pgm_tools.o -o pgm_tools

main.o: main.c menu.h pgm_tools.h
	$(CC) -c main.c

menu.o: menu.c menu.h pgm_tools.h
	$(CC) -c menu.c

pgm_tools.o: pgm_tools.c pgm_tools.h
	$(CC) -c pgm_tools.c

clean:
	rm pgm_tools *.o
