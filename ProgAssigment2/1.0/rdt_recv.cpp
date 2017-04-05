#include <sys/socket.h>
#include <errno.h>
#include <iostream>

int rdt_recv(int socket_descriptor,
             char *buffer,
             int buffer_length,
             int flags,
             struct sockaddr *from_address,
             int *address_length);

int rdt_recv(int socket_descriptor,
       	     char *buffer,
             int buffer_length,
             int flags,
             struct sockaddr *from_address,
             int *address_length)
{
  //Keep reading data while n > 0
  /*slen = sizeof(caddr);
  if (recvfrom(sockfd, (void *)&reqHdr, sizeof(SCS_HDR), 0, (struct sockaddr *)&caddr, &slen) == -1) {
      fprintf(stderr, "%s: error on recvfrom, errno = %d (%s) \n", argv[0],
              errno, strerror(errno));
      continue;
  }*/
}
