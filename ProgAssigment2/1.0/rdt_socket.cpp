//Aurelio Arango
//This will be our connection socket
#include <sys/socket.h>
#include <errno.h>
#include <iostream>

using namespace std;

int rdt_socket(int address_family, int type, int protocol);

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
