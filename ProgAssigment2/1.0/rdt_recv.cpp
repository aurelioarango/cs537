#include <sys/socket.h>
#include <errno.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <cstring>
#include <sys/socket.h>
using namespace std;

extern unsigned short cksum(unsigned char *addr, int nbytes);
struct packet {
        uint16_t cksum; /* Ack and Data */
        uint16_t len;   /* Ack and Data */
        uint32_t ackno; /* Ack and Data */
        uint32_t seqno; /* Data only */
        char data[500]; /* Data only; Not always 500 bytes, can be less */
} packet_t ;

//typedef struct packet packet_t;

int rdt_recv(int socket_descriptor,
       	     char *buffer,
             int buffer_length,
             int flags,
             struct sockaddr *from_address,
             int*address_length)
{
  //Keep reading data while n > 0

  int checksum=1;//to get into loop
  int cal_checksum =0;//calculate a new checksum with the new data
  while(checksum != cal_checksum)
  {

    //get data from the other side
    recvfrom(socket_descriptor, (void *)&packet_t, sizeof(packet_t), flags,
      (struct sockaddr *)&from_address,(socklen_t *) &address_length);
    //chekc for error
    //calculate the address for the data
    int data_index = packet_t.seqno * sizeof(packet_t.data);

    memcpy ( &buffer[data_index], packet_t.data, buffer_length );
    checksum=packet_t.cksum;
    //calculate check sum
    cal_checksum = cksum((unsigned char *)buffer, sizeof(buffer));
  }


  return 0;
}
