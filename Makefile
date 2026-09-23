CC = gcc
CFLAGS = -Wall -Iinclude

TARGET = bin/client
OBJS = obj/main.o obj/mystrfunctions.o obj/myfilefunctions.o

# Installation paths
PREFIX = /usr/local
BINDIR = $(PREFIX)/bin
MANDIR = $(PREFIX)/share/man/man3

MANPAGES = man/man3/mystrlen.3 \
           man/man3/mystrcpy.3 \
           man/man3/mystrncpy.3 \
           man/man3/mystrcat.3 \
           man/man3/wordCount.3 \
           man/man3/mygrep.3

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

$(OBJS):
	$(MAKE) -C src

install: $(TARGET)
	install -d $(BINDIR)
	install -d $(MANDIR)
	install -m 755 $(TARGET) $(BINDIR)/client
	install -m 644 $(MANPAGES) $(MANDIR)/

clean:
	$(MAKE) -C src clean
	rm -f $(TARGET)

.PHONY: all install clean