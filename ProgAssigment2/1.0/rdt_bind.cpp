//Aurelio Arango
//This will be to bind the socket
#include <sys/socket.h>
#include <errno.h>
#include <iostream>

using namespace std;

int rdt_bind(int socket_descriptor, const struct sockaddr * local_address,
            socklen_t address_length);

int rdt_bind(int socket_descriptor, const struct sockaddr * local_address,
            socklen_t address_length)
{

  if ( bind(socket_descriptor, local_address, sizeof(address_length)) == -1 )
  {
      fprintf(stderr, "%s: unable to bind to port '%s', errno = %d (%s) \n", argv[0],
              argv[2], errno, strerror(errno));
      close(socket_descriptor);
      return -1;
  }


}
