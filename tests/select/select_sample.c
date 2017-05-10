#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>

#include <sys/socket.h>
#include <errno.h>

#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>

int inputTimeout (int filedes, unsigned int seconds)
{

  fd_set set;
  struct timeval timeout;

  /* Initialize the file descriptor set. */
  FD_ZERO (&set);
  FD_SET (filedes, &set);

  //need to change to socket_fd


  /* Initialize the timeout data structure. */
  timeout.tv_sec = seconds;
  timeout.tv_usec = 0;

  /* select returns 0 if timeout, 1 if input available, -1 if error. */
  return (select (FD_SETSIZE,
          &set, NULL, NULL,
          &timeout));
}

int main (int argc, char *argv[])
{

  int timeout = 5;
  int socket_fd;
/*  if (argc != 2) {
      fprintf(stderr, "Usage: %s <timeout (secs)>\n", argv[0]);
      return -1;
  }*/
  socket_fd=socket(AF_INET, SOCK_DGRAM, 0);

  //timeout = atoi(argv[1]);

  fprintf (stderr, "select returned %d.\n",
           inputTimeout (socket_fd, timeout));

  //fflush(STDIN_FILENO);

  return 0;
}
