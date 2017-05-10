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
extern int input_timeout (int filedes, unsigned int seconds );

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
  packet ack_t;
  int total_sum =cksum((unsigned char *)buffer,strlen(buffer));
  int unsigned seq_no = 1;
  packet_t.seqno = 1;
  packet_t.ackno = 1;
  int unsigned offset =0;
  int result =0;
  unsigned int timeout =3;
  int again =0;
  cout << "buffer len "<<strlen (buffer) << endl;
  cout << "buffer size " << sizeof(buffer) <<endl;
  //cout << buffer << endl;
  packet_t.len = total_sum;
  while(offset < strlen(buffer) )
  {
    do
    {
      //memset(packet_t.data, 0, sizeof(packet_t));
      //packet_t.len = sizeof(packet_t.data);
      //cout << "len "<< len<<"size of " << " "<< sizeof(packet_t)<<" " << packet_t.data <<" " <<buffer<<endl;
      packet_t.cksum=0;//reset cksum



      //break into chunks
      memset (packet_t.data, 0, 500);
      memcpy ( packet_t.data, buffer+offset, 500 );

      packet_t.cksum =cksum((unsigned char *)packet_t.data,strlen(packet_t.data));
      cout <<"\npacket_t cksum "<< packet_t.cksum <<endl<<endl;
      result = sendto(socket_descriptor, (void *)&  packet_t, sizeof(packet_t), flags, destination_address, address_length);
      //cout << "Result "<<result<<endl;
      if ( result ==-1) {
       perror("Error Sending PACKET ");
        return -1;
      }
      cout << packet_t.data << endl;
      //wait for ack and time it for 3 seconds
      again =input_timeout(socket_descriptor, timeout);
      //if there is no response resend packet
      cout << "\nagain " <<again <<endl<<endl;

      if(again == 1)
      {
        result = recvfrom(socket_descriptor, (void *)&ack_t, sizeof(ack_t), flags,
        destination_address,(socklen_t *) &address_length);
      }


    }while(again==0);


    if ( result ==-1) {
     perror("Error Getting ACK ");
      return -1;
    }
    cout <<"ACK " << ack_t.ackno << " seq_no " << seq_no <<endl;
    if(ack_t.ackno ==  seq_no+1)
    {
      seq_no++;//increase sequence
      //increase offset
      offset +=500;
      packet_t.seqno++;
    }
    cout << "Offset " << offset <<" seq_no " << seq_no <<endl;

  }

  //cout <<" \ntotal cksum "<< total_sum<< "  "<<  ack_t.cksum<< endl;

   return result;

}
