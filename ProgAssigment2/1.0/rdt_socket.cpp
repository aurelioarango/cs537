//Aurelio Arango
//This will be our connection socket
#include <sys/socket.h>
#include <errno.h>
#include <iostream>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

using namespace std;
//for errors
extern int error(const char * f,...);

int rdt_socket(int address_family, int type, int protocol)
{
  int socket_fd;

  socket_fd=socket(address_family, type, protocol);
  if(socket_fd< 0)
  {
    cout << "Can't Create Socket: "<< strerror(errno)<<endl;
    return -1;
  }

  return socket_fd
}
