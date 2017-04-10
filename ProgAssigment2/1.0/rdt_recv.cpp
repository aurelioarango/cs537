#include <sys/socket.h>
#include <errno.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>
using namespace std;

int rdt_recv(int socket_descriptor,
       	     char *buffer,
             int buffer_length,
             int flags,
             struct sockaddr *from_address,
             int *address_length)
{
  //Keep reading data while n > 0

  if (recvfrom(socket_descriptor, (void *)&buffer, buffer_length, flags,
    (struct sockaddr *)&from_address,(socklen_t *) &address_length) == -1) {
    cout <<" error on recvfrom, errno = %d (%s) \n";
      exit(0);
  }
  else
  {
    cout << buffer <<endl;

  }

  return 0;
}
