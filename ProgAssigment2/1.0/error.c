//File from errxit.c
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

int error(const char * f,...)
{
  va_list args;

  va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);
	exit(1);
}
