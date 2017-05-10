#Author: Aurelio Arango
#
#
CC = g++ #compiler used
BLIB = ar
LIBNAME = LibServer.a


CFLAGS = -g -Wall #compilation flags
LIB = -lm	#link libraries
LDFLAGS = -L. #link flags
PROG = server.out #main program executable
OBJ = cksum.o error.o rdt_bind.o rdt_close.o rdt_recv.o rdt_send.o rdt_socket.o server.o  #target files to link
SRC = cksum.cpp error.cpp rdt_bind.cpp rdt_close.cpp rdt_recv.cpp rdt_send.cpp rdt_socket.cpp server.cpp#source files

all : $(PROG)

$(PROG) : $(BLIB)
	$(CC) $(CFLAGS) -o $(PROG) $(LDFLAGS) $(LIBNAME)

clean:
	rm -f *.o $(PROG)

#Create objects and then create libray
$(BLIB): $(LIBNAME)

$(LIBNAME): $(OBJ)
	$(CC) -c $(CFLAGS) $(SRC)
	ar crv $(LIBNAME) $(OBJ)
