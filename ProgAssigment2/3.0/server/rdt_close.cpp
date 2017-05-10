#include <sys/socket.h>
#include <errno.h>
#include <iostream>
#include <unistd.h>

 int rdt_close(int fildes)
 {
  return close(fildes);
 }
