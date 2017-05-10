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
#include <fstream>
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

extern int rdt_recv(int socket_descriptor,
       	     char *buffer,
             int buffer_length,
             int flags,
             struct sockaddr *from_address,
             int address_length);
//rdt close
extern int rdt_close(int fildes);
//validate arguments
extern void check_args(int argc);

extern void check_server(struct hostent * server);

int main(int argc, char *argv[])
{
  char data[12000];//to get the data
  char * port;//port number
  char * ip;//ip address
  int socket_udt;
  //int bind;
  struct sockaddr_in ser_addr;
  //struct hostent * server;


  //check for the number of arguments
  check_args(argc);
  //ip address
  ip = argv[1];
  //port
  port = argv[2];
  //get data
  //data = argv[3];
  //set everything to 0
  //********************** read file data******************************************
  std::ifstream in("Down_the_rabbit_hole.txt");
  std::string file_data((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char> ());


  //copy the data

  memcpy(data,file_data.c_str(), strlen(file_data.c_str()));

//cout << file_data << endl;
  memset((void *)&ser_addr, 0, sizeof(ser_addr));
  ser_addr.sin_family = AF_INET;
  ser_addr.sin_addr.s_addr = inet_addr(ip);
  ser_addr.sin_port = htons(atoi(port));
  //cout <<"family " <<ser_addr.sin_family  <<endl;

  //memset (data, 0, sizeof(data));
  socket_udt = rdt_socket(AF_INET, SOCK_DGRAM, 0);
  //bind to port
  //bind = rdt_bind(socket_udt, )
  //cout << "size of data client "<< data <<endl;
  //rdt_sendto(socket_udt, file_data.c_str(), sizeof(file_data.c_str()),0, (struct sockaddr *) &ser_addr ,sizeof(ser_addr));
  rdt_sendto(socket_udt, data, sizeof(data),0, (struct sockaddr *) &ser_addr ,sizeof(ser_addr));

  //int ser_size = sizeof(ser_addr);
  //rdt_recv(socket_udt,data,sizeof(data),0,(struct sockaddr *) &ser_addr,sizeof(ser_addr));
  //closing socket
  cout << data  <<endl;
  rdt_close(socket_udt);
}
