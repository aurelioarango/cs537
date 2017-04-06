#include <stdio.h>
#include <stdlib.h>

extern unsigned short cksum(unsigned char *addr, int nbytes);

int main(int argc, char *argv[])
{
    unsigned char        *buf;             /* Buffer of packet bytes */
    unsigned short       cksval;           /* 16-bit checksum value  */
    unsigned int         i;                /* Loop counter           */
    int			 bufsize;

    if (argc != 2) {
        printf("Usage: %s <bufsize> \n", __FILE__);
        return -1;
    }

    bufsize = atoi(argv[1]);
    buf = malloc(bufsize);

    /* Load buffer with BUFFER_LEN random bytes */
    for (i = 0; i< bufsize; i++)
       buf[i] = (unsigned char)rand();

    /* Compute the 16-bit checksum */
    cksval = cksum(buf, bufsize);

    /* Output the checksum */
    printf("checksum = %04X \n", cksval);

    free(buf);

}
