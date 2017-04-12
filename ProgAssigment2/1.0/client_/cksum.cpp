/****************************************************************************
 *  Program to compute 16-bit Internet checksum                             *
 ****************************************************************************
 * Notes: 1) Based on the C-code given in RFC 1071 (Computing the Internet  *
 *           Checksum by R. Braden, D. Borman, and C. Partridge, 1988).     *
 ****************************************************************************/
#include <stdio.h>
#include <stdlib.h>

/*****************************************************************************
 * Compute Internet Checksum for count bytes beginning at location addr
 *****************************************************************************/
unsigned short cksum(unsigned char *addr, int nbytes)
{

    unsigned int sum = 0;

    /* Main summing loop */
    while(nbytes > 1)
    {
        sum = sum + *(unsigned short *)addr;
        addr++;
        nbytes -= 2;
    }

    /* Add left-over byte, if any */
    if (nbytes > 0)
        sum = sum + *((unsigned char *) addr);

   /* Fold 32-bit sum to 16 bits */
   while (sum >> 16)
      sum = (sum & 0xFFFF) + (sum >> 16);

   return((unsigned short)~sum);

}