#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


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

    struct sockaddr_in saddr;
    unsigned int clen;
    int    sockfd, port;
    char   *pwd;

    SCS_HDR reqHdr, rspHdr;
    SCS_RSP scsRsp;


    if (argc != 4) {
        fprintf(stderr, "Usage: %s <ip_address> <port> <pwd> \n", argv[0]);
        return -1;
    }

    pwd = argv[3];

    /* Open a UCP based socket connection */
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        fprintf(stderr, "Error opening socket, errno = %d (%s) \n",
                errno, strerror(errno));
        return -1;
    }

    memset((void *)&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = inet_addr(argv[1]);
    saddr.sin_port = htons(atoi(argv[2]));

    /* Send dummy command to server to get time
     * so server knows who to send time */
    reqHdr.cmd = 1;
    reqHdr.pldlen = 0;

    if (sendto(sockfd, (void *)&reqHdr, sizeof(SCS_HDR), 0,(struct sockaddr *) &saddr, sizeof(saddr)) == -1) {
        fprintf(stderr, "Error sending udp pkt to server, errno = %d (%s) \n", errno, strerror(errno));
        close(sockfd);
        return -1;
    }

    /* Wait for response from server (get time) */
    if (recvfrom(sockfd, (void *)&rspHdr, sizeof(rspHdr), 0, (struct sockaddr *)&saddr, (socklen_t *)&clen) == -1) {
        fprintf(stderr, "Error receiving udp pkt from server, errno = %d (%s) \n",
                errno, strerror(errno));
        close(sockfd);
        return -1;
    }

    printf("rspHdr.cmd = %d \n", rspHdr.cmd);
    printf("rspHdr.pldlen = %d \n", rspHdr.pldlen);

    scsRsp.hdr.cmd = 3;
    scsRsp.hdr.pldlen = strlen(pwd);
    strncpy(scsRsp.passwd, pwd, strlen(pwd));

    /* Send the password response */
    if (sendto(sockfd, (void *)&scsRsp, sizeof(SCS_RSP), 0,(struct sockaddr *) &saddr, sizeof(saddr)) == -1) {
        fprintf(stderr, "Error sending udp pkt to server, errno = %d (%s) \n",
                errno, strerror(errno));
        close(sockfd);
        return -1;
    }

    /* Check to see if password was accepted */
    if (recvfrom(sockfd, (void *)&rspHdr, sizeof(SCS_HDR), 0, (struct sockaddr *)&saddr, (socklen_t *)&clen) == -1) {
        fprintf(stderr, "Error receiving udp pkt from server, errno = %d (%s) \n",
                errno, strerror(errno));
        close(sockfd);
        return -1;
    }

    if (rspHdr.cmd == 4) {
        printf("Password was accepted wait for data \n");
    } else {
        printf("Password was rejected by server \n");
    }


    close(sockfd);

    return 0;

}
