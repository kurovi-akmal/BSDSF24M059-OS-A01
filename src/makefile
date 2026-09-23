CC = gcc

CFLAGS = -Wall -I../include
PICFLAGS = -Wall -I../include -fPIC

# Static library
STATIC_LIB = ../lib/libmyutils.a
STATIC_OBJS = ../obj/mystrfunctions.o ../obj/myfilefunctions.o

# Dynamic library
DYNAMIC_LIB = ../lib/libmyutils.so
PIC_OBJS = ../obj/mystrfunctions_pic.o ../obj/myfilefunctions_pic.o

# Executables
STATIC_TARGET = ../bin/client_static
DYNAMIC_TARGET = ../bin/client_dynamic

MAIN_OBJ = ../obj/main.o

all: $(STATIC_TARGET) $(DYNAMIC_TARGET)


# =========================
# Static Library
# =========================

$(STATIC_LIB): $(STATIC_OBJS)
	ar rcs $(STATIC_LIB) $(STATIC_OBJS)

$(STATIC_TARGET): $(MAIN_OBJ) $(STATIC_LIB)
	$(CC) $(MAIN_OBJ) $(STATIC_LIB) -o $(STATIC_TARGET)


# =========================
# Dynamic Library
# =========================

$(DYNAMIC_LIB): $(PIC_OBJS)
	$(CC) -shared -o $(DYNAMIC_LIB) $(PIC_OBJS)

$(DYNAMIC_TARGET): $(MAIN_OBJ) $(DYNAMIC_LIB)
	$(CC) $(MAIN_OBJ) -L../lib -lmyutils -o $(DYNAMIC_TARGET)


# =========================
# Normal Object Files
# =========================

../obj/main.o: main.c ../include/mystrfunctions.h ../include/myfilefunctions.h
	$(CC) $(CFLAGS) -c main.c -o ../obj/main.o

../obj/mystrfunctions.o: mystrfunctions.c ../include/mystrfunctions.h
	$(CC) $(CFLAGS) -c mystrfunctions.c -o ../obj/mystrfunctions.o

../obj/myfilefunctions.o: myfilefunctions.c ../include/myfilefunctions.h
	$(CC) $(CFLAGS) -c myfilefunctions.c -o ../obj/myfilefunctions.o


# =========================
# Position Independent Object Files
# =========================

../obj/mystrfunctions_pic.o: mystrfunctions.c ../include/mystrfunctions.h
	$(CC) $(PICFLAGS) -c mystrfunctions.c -o ../obj/mystrfunctions_pic.o

../obj/myfilefunctions_pic.o: myfilefunctions.c ../include/myfilefunctions.h
	$(CC) $(PICFLAGS) -c myfilefunctions.c -o ../obj/myfilefunctions_pic.o


# =========================
# Clean
# =========================

clean:
	rm -f ../obj/*.o
	rm -f ../lib/libmyutils.a
	rm -f ../lib/libmyutils.so
	rm -f ../bin/client_static
	rm -f ../bin/client_dynamic

.PHONY: all clean