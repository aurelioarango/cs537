
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
//rdt close
extern rdt_close(int fildes);
//validate arguments
extern check_args(int argc);


int main(int argc, char *argv[])
{
  char * data;//to get the data
  char * port;//port number
  char * ip;//ip address
  int socket_udt;
  int bind;
  struct sockaddr_in ser_addr;
  struct hostent * server;


  //check for the number of arguments
  check_args(argc);
  //ip address
  ip = argv[1];
  //port
  port = argv[2];
  //get data
  data = argv[3];
  //get host name
  server = gethostbyname(argv[1]);
  //check if server name is not empty
  check_server(server);


  memset((void *)&ser_addr, 0, sizeof(ser_addr));
  ser_addr.sin_family = AF_INET;
  ser_addr.sin_addr.s_addr = inet_addr(argv[1]);
  ser_addr.sin_port = htons(atoi(argv[2]));

  /* Send dummy command to server to get time
   * so server knows who to send time */
  //reqHdr.cmd = 1;
  //reqHdr.pldlen = 0;


/*  bzero((char *) & ser_addr, sizeof(ser_addr) );
  serv_addr.sin_family = AF_INET;

  bcopy( (char *) server->h_addr,
         (char *)&ser_addr.sin_addr.s_addr,
          server->h_length );
  //get port number
  port = atoi(argv[2]);

  serv_addr.sin_port = htons(port);*/

  socket_udt = rdt_socket(AF_INET, SOCK_DGRAM, 0);
  //bind to port
  //bind = rdt_bind(socket_udt, )
  rdt_sendto(socket_udt, data, sizeof(data),
    0, (struct sockaddr *) r_addr ,sizeof(r_addr));

  rdt_recv(socket_udt,data,sizeof(data),
    0,(struct sockaddr *) r_addr, sizeof(r_addr));
  //closing socket
  rdt_close(socket_udt);
}
