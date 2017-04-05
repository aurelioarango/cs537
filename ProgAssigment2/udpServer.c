#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <time.h>
#include <unistd.h>

typedef struct {
    unsigned short cmd;
    unsigned int   pldlen;
} SCS_HDR;

typedef struct {
    SCS_HDR    hdr;
    char       passwd[50];
} SCS_RSP;

typedef struct {
    SCS_HDR    hdr;
    int        pktId;
    char       data[1000];
} SCS_DATA;

int main(int argc, char *argv[])
{

    struct sockaddr_in  saddr, caddr;
    unsigned int slen;
    int    sockfd;
    char   buf[1000];
    char   *pwd;

    SCS_HDR  reqHdr, rspHdr;
    SCS_RSP  scsRsp;

    if (argc != 4) {
       fprintf(stderr, "%s <ip-address> <port> <password>\n", argv[0]);
       return -1;
    }

    /* Create the socket */
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
       fprintf(stderr, "%s : cannot create socket, errno = %d, (%s) \n", argv[0],
               errno, strerror(errno));
       return -1;
    }

    pwd = argv[3];

    memset((void *)&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = inet_addr(argv[1]);
    saddr.sin_port = htons(atoi(argv[2]));

    /* bind service to a port */
    if (bind(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)) == -1) {
        fprintf(stderr, "%s: unable to bind to port '%s', errno = %d (%s) \n", argv[0],
                argv[2], errno, strerror(errno));
        close(sockfd);
        return -1;
    }

    while (1) {
        /* Waiting for a join request from a client */
        slen = sizeof(caddr);
        if (recvfrom(sockfd, (void *)&reqHdr, sizeof(SCS_HDR), 0, (struct sockaddr *)&caddr, &slen) == -1) {
            fprintf(stderr, "%s: error on recvfrom, errno = %d (%s) \n", argv[0],
                    errno, strerror(errno));
            continue;
        }

        rspHdr.cmd = 2;
        rspHdr.pldlen = 0;

        /* Send password response to client */
        if (sendto(sockfd, (void *)&rspHdr, sizeof(SCS_HDR), 0, (struct sockaddr *)&caddr, slen) == -1) {
            fprintf(stderr, "Error sending to client, errno = %d (%s) \n",
            errno, strerror(errno));
        }

        /* Wait for password response */
        if (recvfrom(sockfd, (void *)&scsRsp, sizeof(SCS_RSP), 0, (struct sockaddr *)&caddr, &slen) == -1) {
            fprintf(stderr, "%s: error on recvfrom, errno = %d (%s) \n", argv[0],
                    errno, strerror(errno));
            continue;
        }

        /* Set to password rejected then overwrite if a match */
        rspHdr.cmd = 7;
        rspHdr.pldlen = 0;

        if (strcmp(scsRsp.passwd, pwd) == 0) {
            rspHdr.cmd = 4;
        }

        if (sendto(sockfd, (void *)&rspHdr, sizeof(SCS_HDR), 0, (struct sockaddr *)&caddr, slen) == -1) {
            fprintf(stderr, "Error sending to client, errno = %d (%s) \n",
            errno, strerror(errno));
        }
        
 
    }

    return 0;

}