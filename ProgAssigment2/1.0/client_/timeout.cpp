#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
//Sample from Class
int input_timeout (int filedes, unsigned int seconds)
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
