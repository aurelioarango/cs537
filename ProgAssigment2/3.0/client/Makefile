#Author: Aurelio Arango
#
#

CC = g++ #compiler used
CFLAGS = -g -Wall #compilation flags
BLIB = ar
LIB = -lm	#link libraries
LDFLAGS = -L. #link flags
LIBNAME = LibClient.a
DIRSRC = ../
PROG = client.out #main program executable
OBJ = cksum.o error.o rdt_bind.o rdt_close.o rdt_recv.o rdt_send.o rdt_socket.o client.o timeout.o#target files to link
SRC = cksum.cpp error.cpp rdt_bind.cpp rdt_close.cpp rdt_recv.cpp rdt_send.cpp rdt_socket.cpp timeout.cpp client.cpp #source files


all : $(PROG)

$(PROG) : $(BLIB)
	$(CC) $(CFLAGS) -o $(PROG) $(LDFLAGS) $(LIBNAME)
#$(PROG): $(OBJ)
#	$(CC) -c $(CFLAGS) $(SRC)
#	$(CC) $(CFLAGS) -o $(PROG) $(OBJ) $(LDFLAGS) $(LIB)

clean:
	rm -f *.o *.a $(PROG)

$(BLIB): $(LIBNAME)

$(LIBNAME): $(OBJ)
	$(CC) -c $(CFLAGS) $(SRC)
	#$(CC) $(CFLAGS) -o $(PROG) $(OBJ) $(LDFLAGS) $(LIB)
	ar crv $(LIBNAME) $(OBJ)
