.DEFAULT_GOAL:	ALL

CC	=	gcc

OUTPUT: main.o
	gcc	main.o	-o	OUTPUT

MAIN:	main.c
	gcc	-c	main.c

CLEAN:
	rm	*.o	 OUTPUT

ALL:	CLEAN	MAIN	OUTPUT