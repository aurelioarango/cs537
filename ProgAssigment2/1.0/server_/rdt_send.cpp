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
} ;
//defining the struct
//typedef struct packet packet_t;

int rdt_sendto(int socket_descriptor,
              char *buffer,
              int buffer_length,
              int flags,
              struct sockaddr *destination_address,
              int address_length){

  packet packet_t;
  int ck_sum =cksum((unsigned char *)buffer,strlen(buffer));
  packet_t.seqno = 0;
  packet_t.ackno = 0;
  unsigned int len = buffer_length;
  //cout << buffer << " len " <<len << " "<<buffer_length <<endl;
  //Break data into packets and send it over UDP use a foorloop to keep sending the data.
  /* while ( len > sizeof(packet_t.data) )
   {

     packet_t.len = sizeof(packet_t.data);
     packet_t.cksum =ck_sum;
     //copy message into packet.data and use packet size
     memcpy ( packet_t.data, buffer, sizeof(packet_t.data) );
     //traverse the data message
     //packet_l.seqno++;
     //packet_l.ackno++;
     //increate the pointer by the size of data copy from it
     buffer += sizeof(packet_t.data);
     len -= sizeof(packet_t.data);


     //send the data
     if (sendto(socket_descriptor, (void *)& packet_t, sizeof(packet_t), flags, (struct sockaddr *)&destination_address, address_length) == -1) {
          error("Error sending to client, errno \n");
         return -1;
     }
     packet_t.seqno++;
     packet_t.ackno++;
   }*/
   //send the last bit of data
   //packet_l.seqno++;
   //packet_l.ackno++;


   //memset(packet_t.data, 0, sizeof(packet_t));
   packet_t.len = sizeof(packet_t.data);
   //cout << "len "<< len<<"size of " << " "<< sizeof(packet_t)<<" " << packet_t.data <<" " <<buffer<<endl;
   packet_t.cksum =ck_sum;
   memcpy ( packet_t.data, buffer, strlen(buffer)+1 );
   int result =0;
   result = sendto(socket_descriptor, (void *)&  packet_t, sizeof(packet_t), flags, destination_address, address_length);
   //cout << "Result "<<result<<endl;
   if (  result ==-1) {
      perror("Error Sending ");
       //error("Error sending to client\n", errno);
      // printf("Error no %d %s  \n",errno ,strerror(errno) );
       return -1;
   }

   return result;

}
