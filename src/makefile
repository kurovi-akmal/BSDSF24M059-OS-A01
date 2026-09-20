CC = gcc
CFLAGS = -Wall -I../include

OBJS = ../obj/main.o ../obj/mystrfunctions.o ../obj/myfilefunctions.o

all: $(OBJS)

../obj/main.o: main.c ../include/mystrfunctions.h ../include/myfilefunctions.h
	$(CC) $(CFLAGS) -c main.c -o ../obj/main.o

../obj/mystrfunctions.o: mystrfunctions.c ../include/mystrfunctions.h
	$(CC) $(CFLAGS) -c mystrfunctions.c -o ../obj/mystrfunctions.o

../obj/myfilefunctions.o: myfilefunctions.c ../include/myfilefunctions.h
	$(CC) $(CFLAGS) -c myfilefunctions.c -o ../obj/myfilefunctions.o

clean:
	rm -f ../obj/*.o

.PHONY: all clean