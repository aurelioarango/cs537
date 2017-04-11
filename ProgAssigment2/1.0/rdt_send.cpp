#include <sys/socket.h>
#include <errno.h>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>
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
};

typedef struct packet packet_t;

int rdt_sendto(int socket_descriptor,
              char *buffer,
              int buffer_length,
              int flags,
              struct sockaddr *destination_address,
              int address_length)
{

  int ck_sum =cksum(&buffer,strlen(buffer));
  packet_t.seqno = 0;
  packet_t.ackno = 0;
  int len = address_length;
  //Break data into packets and send it over UDP use a foorloop to keep sending the data.
   while ( len > sizeof(packet_t.data) )
   {
     packet_t.seqno++;
     packet_t.ackno++;
     packet_t.len = sizeof(packet.data);;
     packet_t.cksum =ck_sum;
     //copy message into packet.data and use packet size
     memcpy ( packet_t.data, buffer, sizeof(packet_t.data) );
     //traverse the data message
     buffer += sizeof(packet.data);
     len -= sizeof(packet.data);


     //send the data
     if (sendto(socket_descriptor, (void *)& packet_t, sizeof(packet_t), flags, (struct sockaddr *)&destination_address, address_length) == -1) {
         cout << "Error sending to client, errno = %d (%s) \n" <<endl;
         return -1;
     }
   }
   //send the last bit of data
   packet_t.seqno++;
   packet_t.ackno++;
   packet_t.len = sizeof(packet.data);;
   packet_t.cksum =ck_sum;
   memcpy ( packet_t.data, buffer, sizeof(packet_t.data) );
   if (sendto(socket_descriptor, (void *)&  packet_t, sizeof(packet_t), flags, (struct sockaddr *)&destination_address, address_length) == -1) {
       cout << "Error sending to client, errno = %d (%s) \n" <<endl;
       return -1;
   }

   return 0;

}
