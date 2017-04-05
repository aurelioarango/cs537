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
  int sock, length, n;
  struct sockaddr_in server, from;
  struct hostent *hp;
  char buffer[256];
  
  if(argc != 3)
  {
    cout << "<server> <port>"<<endl;
    exit(1);
  }
  sock = socket (AF_INET, SOCK_DRGRAM, 0);
  
  if(sock <0)
  {
    error("socket");
  }
  server.sin_family=AF_INET;
  hp = gethostbyname(argv[1]);
  if(hp ==0)
  {
    error("unknown host");
  }
  bcopy ((char *) hp->h_addr,(char *) &server.sing_addr, hp->h_length );
  server.sin_port = btons(atoi(argv[2]));
  length = sizeof(struct sockaddr_in);
  cout <<"Enter message: "<<endl;
  
  bzero(buffer, 256);
  fgets(buffer, 255, stdin);
  n=sendto(sock, buffer, strlen(buffer), 0, &server, length);
  if(n<0)
    error("send to");
  n=sendfrom(sock, buffer, 256, 0, &from, length);
  if(n<0)
  write(1, buffer, n);
  
  
  
}