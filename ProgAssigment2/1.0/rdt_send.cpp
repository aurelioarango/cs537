#include <sys/socket.h>
#include <errno.h>
#include <iostream>
//use error handling
extern int error(const char * f,...);

struct packet {
        uint16_t cksum; /* Ack and Data */
        uint16_t len;   /* Ack and Data */
        uint32_t ackno; /* Ack and Data */
        uint32_t seqno; /* Data only */
        char data[500]; /* Data only; Not always 500 bytes, can be less */
};

typedef struct packet packet_t;

int rdt_sendto(int socket_descriptor,
              char *buffer,
              int buffer_length,
              int flags,
              struct sockaddr *destination_address,
              int address_length)
{

  //Break data into packets and send it over UDP use a foorloop to keep sending the data.
  if (sendto(socket_descriptor, (void *)& buffer, buffer_length, flags, (struct sockaddr *)&destination_address, address_length) == -1) {
      fprintf(stderr, "Error sending to client, errno = %d (%s) \n",
      errno, strerror(errno));
  }


}
