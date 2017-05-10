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
}  ;

//typedef struct packet packet_t;

int rdt_recv(int socket_descriptor,
       	     char *buffer,
             int buffer_length,
             int flags,
             struct sockaddr *from_address,
             int  address_length,
             char *d_flag)
{
  //Keep reading data while n > 0
  packet packet_t;
  packet ack_t;
  int checksum=1;//to get into loop
  int cal_checksum =0;//calculate a new checksum with the new data
  unsigned int  seq_no=1;//first sequence number
  unsigned int offset =0;
  int result=0;
  int totalcksum =0;
  bool keepgoing = true;
  /*if(strcmp(d_flag,"d" ) == 0 || strcmp(d_flag,"a")==0)
  {
    //drop packet
    cout <<"drop"<<endl;
    //memset (packet_t.data, 0, 500);
  }*/
    while(keepgoing)
    {
      //keep reading while it is not the same seq_no and ack
      do
      {
        packet_t.len =0;
        memset (packet_t.data, 0, 500);
        packet_t.cksum=0;
        result = recvfrom(socket_descriptor, (void *)&packet_t, sizeof(packet_t), flags,
        from_address,(socklen_t *) &address_length);

        if (  result ==-1) {
           perror("Error Getting data ");;
            return -1;
        }

        /*if(strcmp(d_flag,"d" )==0 || strcmp(d_flag,"a" )==0)
        {
          //drop packet
          //cout <<"drop"<<endl;
          memset (packet_t.data, 0, 500);
        }
        else
        {
          memcpy ( buffer+offset, packet_t.data, 500 );
        }*/
        memcpy ( buffer+offset, packet_t.data, 500 );


        checksum=packet_t.cksum;
        cal_checksum =0;
        cal_checksum = cksum((unsigned char *)packet_t.data, strlen(packet_t.data));
        //int other_cksum = cksum((unsigned char *)buffer, sizeof(buffer));
        //check the sequence number
        //usleep(2000);

        cout << " cal_checksum " <<cal_checksum << " checksum " << checksum<<endl;
        cout << " seq_no "<< seq_no << " packet_t seq_no " << packet_t.seqno <<endl;
      //}while (seq_no != packet_t.seqno && cal_checksum != packet_t.cksum );
      }while (seq_no != packet_t.seqno );
      totalcksum += checksum;
      //increase sequence and send ack no
      ack_t.ackno = packet_t.seqno +1;
      //make it sleep
      /*if(strcmp(d_flag,"D" )==0 || strcmp(d_flag,"a" )==0)
      {
        //delay
        //cout <<"sleep"<<endl;
        //usleep(4000);
      }*/


      //send ACK
      result = sendto(socket_descriptor, (void *)&  ack_t, sizeof(ack_t), flags, from_address, address_length);
      cout << packet_t.data << endl;
      //cout << "Result "<<result<<endl;
      if (  result ==-1) {
         perror("Error Sending ACK ");
          return -1;
      }
      //if the check sum is equal then is done.
      cout << "\nACK " << packet_t.ackno << " cal_checksum " <<cal_checksum << " checksum " << checksum<<endl;
      cout << "\nACK.ackno " << ack_t.ackno << endl;

      int sum = cksum((unsigned char *)buffer, strlen(buffer));
      cout <<"\n totalcksum " <<packet_t.len << " cal_checksum " << cal_checksum << " sum "<< sum <<endl<<endl;
      if(sum == packet_t.len)
      {
        keepgoing=false;

      }
      offset+=500;
      seq_no++;
      cout << "keepgoing "<< keepgoing << endl;

    }


    //increase ack

  //cout <<"Data: " <<buffer << " sum "<< checksum<<" new cksum " << cal_checksum<<endl;
  cout << "ACK " << packet_t.ackno << endl;
  return 0;
}
