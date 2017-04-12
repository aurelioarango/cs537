#include <sys/socket.h>
#include <errno.h>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <cstring>
#include <stdio.h>
using namespace std;
//use error handling
extern int error(const char * format,...);
extern unsigned short cksum(unsigned char *addr, int nbytes);
struct packet {
        uint16_t cksum; /* Ack and Data */
        uint16_t len;   /* Ack and Data */
        uint32_t ackno; /* Ack and Data */
        uint32_t seqno; /* Data only */
        char data[500]; /* Data only; Not always 500 bytes, can be less */
} packet_l;
//defining the struct
//typedef struct packet packet_l;

int rdt_sendto(int socket_descriptor,
              char *buffer,
              int buffer_length,
              int flags,
              struct sockaddr *destination_address,
              int address_length){

  int ck_sum =cksum((unsigned char *)buffer,strlen(buffer));
  packet_l.seqno = 0;
  packet_l.ackno = 0;
  unsigned int len = address_length;
  //Break data into packets and send it over UDP use a foorloop to keep sending the data.
   while ( len > sizeof(packet_l.data) )
   {

     packet_l.len = sizeof(packet_l.data);
     packet_l.cksum =ck_sum;
     //copy message into packet.data and use packet size
     memcpy ( packet_l.data, buffer, sizeof(packet_l.data) );
     //traverse the data message
     //packet_l.seqno++;
     //packet_l.ackno++;
     //increate the pointer by the size of data copy from it
     buffer += sizeof(packet_l.data);
     len -= sizeof(packet_l.data);


     //send the data
     if (sendto(socket_descriptor, (void *)& packet_l, sizeof(packet_l), flags, (struct sockaddr *)&destination_address, address_length) == -1) {
         cout << "Error sending to client, errno = %d (%s) \n" <<endl;
         return -1;
     }
     packet_l.seqno++;
     packet_l.ackno++;
   }
   //send the last bit of data
   //packet_l.seqno++;
   //packet_l.ackno++;
   packet_l.len = sizeof(packet_l.data);;
   packet_l.cksum =ck_sum;
   memcpy ( packet_l.data, buffer, sizeof(packet_l.data) );
   if (sendto(socket_descriptor, (void *)&  packet_l, sizeof(packet_l), flags, (struct sockaddr *)&destination_address, address_length) == -1) {
       cout << "Error sending to client, errno = %d (%s) \n" <<endl;
       return -1;
   }

   return 0;

}
