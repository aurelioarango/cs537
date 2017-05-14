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
	$(CC) $(CFLAGS) -o $(PROG) $(LDFLAGS) $(LIBNAME) #build client.a with LibCient.a
#$(PROG): $(OBJ)
#	$(CC) -c $(CFLAGS) $(SRC)
#	$(CC) $(CFLAGS) -o $(PROG) $(OBJ) $(LDFLAGS) $(LIB)

clean:
	rm -f *.o *.a $(PROG)

#funtion to build the library with the name libClient.a
$(BLIB): $(LIBNAME)
#build tibClient. a with the objects
$(LIBNAME): $(OBJ)
	#compiel the source into objects
	$(CC) -c $(CFLAGS) $(SRC)
	#$(CC) $(CFLAGS) -o $(PROG) $(OBJ) $(LDFLAGS) $(LIB)
	#build the library with the objects
	ar crv $(LIBNAME) $(OBJ)
