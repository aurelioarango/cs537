#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <cstdio>

using namespace std;
//open socket
extern int rdt_socket(int address_family, int type, int protocol);
//bind socket
extern int rdt_bind(int socket_descriptor, const struct sockaddr * local_address,
            socklen_t address_length);

extern int rdt_sendto(int socket_descriptor,
              char *buffer,
              int buffer_length,
              int flags,
              struct sockaddr *destination_address,
              int address_length);
//rcv data
extern int rdt_recv(int socket_descriptor,
       	     char *buffer,
             int buffer_length,
             int flags,
             struct sockaddr *from_address,
             int address_length,
             char *d_flag);
//rdt close
extern int rdt_close(int fildes);
//validate arguments
extern void check_args(int argc);

extern  void check_serv_args(int argc);

extern  void check_server(struct hostent * server);

int main(int argc, char *argv[])
{
  char data[12000];//to get the data
  char * port;//port number
  char * flag;
  //char * ip;//ip address
  int socket_udt;
  //int bind;
  struct sockaddr_in ser_addr;
  //struct hostent * server;

  //check for the number of arguments
  check_serv_args(argc);
  //ip address
  //ip = argv[1];
  //port
  port = argv[1];
  if(argc ==3)
  {
    flag = argv[2];
    cout << "flag "<<flag << endl;
  }
  else
  {
    flag = NULL;
  }


  //get host name

  //server = gethostbyname(argv[1]);
  //from_address
  //check if server name is not empty
  //check_server(server);
  //cout <<"port " <<port << endl;
  socket_udt = rdt_socket(AF_INET, SOCK_DGRAM, 0);

  //set data to 0
  memset((void *)&ser_addr, 0, sizeof(ser_addr));
  ser_addr.sin_family = AF_INET;
  ser_addr.sin_addr.s_addr = INADDR_ANY;//inet_addr(ip);
  ser_addr.sin_port = htons(atoi(port));
  //cout << "UDT port "<< port <<endl;
  //cout <<"UDT port "<<ser_addr.sin_port <<endl;
  //bind service
  rdt_bind(socket_udt,(struct sockaddr *) &ser_addr,sizeof(ser_addr));

  while (1)
  /* Waiting for a join request from a client */
  {
    rdt_recv(socket_udt,data,sizeof(data),
      0,(struct sockaddr *) &ser_addr, sizeof(ser_addr),flag );

      //rdt_sendto(socket_udt, data, sizeof(data),
      //0, (struct sockaddr *) &ser_addr ,sizeof(ser_addr));
    cout <<"TOTAL DATA: "<< data << endl;
    cout << "\n\nDONE!!! "<<endl;
    memset (data, 0, 12000);
  }




  //closing socket
  rdt_close(socket_udt);

  return 0;
}
