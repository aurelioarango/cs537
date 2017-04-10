//File from errxit.c
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <iostream>

using namespace std;

int error(const char * format,...)
{
  va_list args;

  va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);
	exit(1);
}

void check_args(int argc)
{

  if(argc != 4)
  {
    cout << "Usage: %s <ip_address> <port> <data> "<<endl;
    exit(0);
  }

}

void check_server(hostent * server)
{
  if (server == NULL) {
        fprintf(stderr,"Error getting host, h_errno = %d (%s) \n",
                h_errno,hstrerror(h_errno));
        exit(0);
    }
}
