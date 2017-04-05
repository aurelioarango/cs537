#include <sys/types.h>
#include <sys/socket.h>
#include <netime/in.h>
#include <netdb.h>
#include <stdio.h>
#include <arpa/inet.h>

void error(char * msg)
{
  error(msg);
  exit(0);
}

int main(int argc, char *argv[])
{
  int sock, length, fromlen, n;
  struct sockaddr_in server;
  struct sockaddr_in from;
  char buf[512];
  
  if(arc < 2)
  {
    cout << "Error, no port provided\n" <<endl;
    exit (0);
  }
  
  sock= socket(AF_INET, SOCK_DGRAM, 0);
  
  if(sock <0)
  {
    error("opening socket");
  }
  bzero(&server,length);
  server.sin_family=AF_INET;
  server.sin_addr.s_addr=INADDR_ANY;
  server.sing_port=htons(atoi(argv[1]));
  
  if(bind(sock,(struct sockaddr *)&server,length ) <0)
  {
    error("binding");
  }
  fromlen = sizeof(struct sockaddr_in);
  
  while(1)
  {
    n = recvfrom(sockm buf, 512, 0, (struct sockaddr *) &from, &fromlen);
    if(n<0)
    {
      error("recvfrom");
    }
    write(1, "Received a datagram: ", 21);
    write(1, buf,n);
    n = sendto(sock, "Got your message\n", 17, 0, (struct sockaddr *)&from, fromlen);
    if(n<0)
    {
      error("sendto");
    }
    
  }
  
  
  
}