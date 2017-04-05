#include <sys/socket.h>
#include <errno.h>
#include <iostream>

int rdt_sendto(int socket_descriptor,
               char *buffer,
               int buffer_length,
               int flags,
               struct sockaddr *destination_address,
               int address_length);


int rdt_sendto(int socket_descriptor,
              char *buffer,
              int buffer_length,
              int flags,
              struct sockaddr *destination_address,
              int address_length)
{

  //Break data into packets and send it over UDP use a foorloop to keep sending the data.


  /*if (sendto(sockfd, (void *)&rspHdr, sizeof(SCS_HDR), 0, (struct sockaddr *)&caddr, slen) == -1) {
      fprintf(stderr, "Error sending to client, errno = %d (%s) \n",
      errno, strerror(errno));
  }*/


}
