#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>

int inputTimeout (int filedes, unsigned int seconds)
{

  fd_set set;
  struct timeval timeout;

  /* Initialize the file descriptor set. */
  FD_ZERO (&set);
  FD_SET (filedes, &set);

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

  int timeout = 0;

  if (argc != 2) {
      fprintf(stderr, "Usage: %s <timeout (secs)>\n", argv[0]);
      return -1;
  }

  timeout = atoi(argv[1]);

  fprintf (stderr, "select returned %d.\n",
           inputTimeout (STDIN_FILENO, timeout));

  fflush(STDIN_FILENO);

  return 0;
}