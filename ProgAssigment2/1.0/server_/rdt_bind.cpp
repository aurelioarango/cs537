//Aurelio Arango
//This will be to bind the socket
#include <sys/socket.h>
#include <errno.h>
#include <iostream>
#include <unistd.h>

extern int error(const char * format,...);
using namespace std;

int rdt_bind(int socket_descriptor, const struct sockaddr * local_address,
            socklen_t address_length)
{
  int result =0;
  cout << socket_descriptor << " "<< endl;
  result = bind(socket_descriptor, local_address, address_length);
  if ( result <= -1 )
  {
      //cout << "Unable to bind to port '%s', errno = %d (%s) \n";
      error("Unable to bind to port\n");
      close(socket_descriptor);
      return -1;
  }
  cout << "Bind result " <<result <<endl;
  return socket_descriptor;
}
