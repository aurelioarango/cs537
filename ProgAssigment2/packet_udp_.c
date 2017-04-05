typedef struct Packet
{
 int sequence;
 int length;
 int more;
 unsigned char data[10]; // I use 10 here to demonstrate.
} Packet;


void main ( int argc, char * argv [] )
{
 char * message = "This message is longer than 10 characters.";
 SendMessage ( message, strlen(message) );
}


void SendMessage ( char * message, int length )
{
 struct Packet packet;
 int sequence = 0;

 while ( length > sizeof(packet.data) )
 {
  packet.sequence = sequence++;
  packet.length = sizeof(packet.data);
  packet.more = true;
  memcpy ( packet.data, message, sizeof(packet.data) );
  message += sizeof(packet.data);
  length -= sizeof(packet.data);
  SendPacket ( &packet );
 }
 packet.sequence = sequence;
 packet.length = length;
 packet.more = false;
 memcpy ( packet.data, message, length );
 SendPacket ( &packet );
}
/////////Assemble

void ReceiveMessage ( char * message, int maxLen )
{
 struct Packet packet;
 while (ReceivePacket(&packet))
 {
  int position = packet.sequence * sizeof(packet.data);
  memcpy ( &message[position], packet.data, message.length );
 }
}

////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/wait.h>

#define MYPORT 4950

struct packet
{
      int seq_no;
      char flag;
      char buffer[256];
}mypacket;

char temp_buffer[256];
int i;

int main(int argc, char *argv[])
{
      int sockfd;
      struct sockaddr_in their_addr;
      struct hostent *he;
      int numbytes;
      mypacket mp;

      if (argc != 3)
      {
            fprintf(stderr,"usage: talker hostname message\n");
            exit(1);
      }

      if ((he=gethostbyname(argv[1])) == NULL)
      {
            herror("gethostbyname");
            exit(1);
      }

      if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
      {
            perror("socket");
            exit(1);
      }

      their_addr.sin_family = AF_INET;
      their_addr.sin_port = htons(MYPORT);

      their_addr.sin_addr = *((struct in_addr *)he->h_addr);

      bzero(&(their_addr.sin_zero), 8);

      mp.seq_no = 1;
      mp.flag = 0;

      if ((numbytes=sendto(sockfd, argv[2], strlen(argv[2]), 0, &mypacket, sizeof(mypacket),(struct sockaddr *)&their_addr, sizeof(struct sockaddr))) == -1)
      {
            perror("sendto");
            exit(1);
      }

      printf("Sent %d bytes to %s\n",numbytes,inet_ntoa(their_addr));

      close(sockfd);
      return 0;
}



/*client*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>

#define MYPORT 4950

#define MAXBUFLEN 100

struct packet
{
      int seq_no;
      char flag;
      char buffer[250];
}mypacket;

main()
{
      int sockfd;
      struct sockaddr_in my_addr;
      struct sockaddr_in their_addr;
      int addr_len, numbytes;
      char buf[MAXBUFLEN];
      mypacket mp;
      int tempseq_no;
      
      tempseq_no = 0;

      if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
      {
            perror("socket");
            exit(1);
      }

      my_addr.sin_family = AF_INET;
      my_addr.sin_port = htons(MYPORT);
      
      my_addr.sin_addr.s_addr = INADDR_ANY;
      bzero(&(my_addr.sin_zero), 8);
      
      if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
      {
            perror("bind");
            exit(1);
      }
      
      while(1)
      {
      addr_len = sizeof(struct sockaddr);
      if ((numbytes=recvfrom(sockfd, buf, MAXBUFLEN, 0, (struct sockaddr *)&their_addr,             &addr_len)) == -1)
      {
            perror("recvfrom");
            exit(1);
      }
      
      if (mypacket.seq_no < tempseq_no)
      {
      printf("Got packet from %s\n",inet_ntoa(their_addr.sin_addr));
      printf("Packet is %d bytes long\n",numbytes);

      buf[numbytes] = '\0';
      printf("Packet contains \"%s\"\n",buf);
      }
      else tempseq_no = mypacket.seq_no

      if (tempseq_no < mypacket.seq_no)
      {
      printf("ERROR: The sequence number of the recieved packet is too small")
      }
      
      close(sockfd);
}
