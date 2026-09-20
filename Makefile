CC = gcc
CFLAGS = -Wall -Iinclude

TARGET = bin/client
OBJS = obj/main.o obj/mystrfunctions.o obj/myfilefunctions.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

$(OBJS):
	$(MAKE) -C src

clean:
	$(MAKE) -C src clean
	rm -f $(TARGET)

.PHONY: all clean