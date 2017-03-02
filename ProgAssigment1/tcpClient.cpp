#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char *argv[])
{

    int    sockfd,  port, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    char *msg;

    if (argc != 4) {
       fprintf(stderr,"usage %s <hostname> <port> <msg>\n", argv[0]);
       exit(0);
    }

    /* Create the TCP socket for communication */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)  {
        fprintf(stderr, "Error opening socket, errno = %d (%s) \n",
                errno, strerror(errno));
        return -1;
    }

    /* Get the host name (i.e. the name or IP address of the server) */
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"Error getting host, h_errno = %d (%s) \n",
                h_errno,hstrerror(h_errno));
        return -1;
    }

    /* Setup the socket for network comms */
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;

    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
           server->h_length);

    /* Get the service name/port number */
    port = atoi(argv[2]);
    /* have to convert the port number to network format */
    serv_addr.sin_port = htons(port);

    /* Make a connection request to the server */
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)  {
        fprintf(stderr, "Error connecting to socket, errno = %d (%s) \n",
                errno, strerror(errno));
        return -1;
    }

    /* Get the client request from the command line */
    msg = argv[3];

    /* Make the client request to the server */
    n = write(sockfd,msg,strlen(msg));
    if (n < 0) {
        fprintf(stderr, "Error writing to socket, errno = %d (%s) \n",
                errno, strerror(errno));
        return -1;
    }

    bzero(buffer,256);

    string message;
    message = msg;
    if(message.find("GET")!= -1 || message.find("HEAD")!= -1)
    {
      //create file
      //fstream fileout;
      string buff;

      //memset((void *)buffer, 0, 256);

      //only do header
      if( message.find("HEAD")!= -1)
      {
        FILE * hfile;
        hfile = fopen("header_2", "w");
        //writing to file
        n = read(sockfd,buffer,255);
        //cout << "n = "<< n<<endl;
        while(n>0)
        {
          fputs(buffer, hfile);
          buff = buffer;
          //cout <<"buff n= "<< n<< " "<<buff<<endl;
          bzero(buffer,256);
          n = read(sockfd,buffer,255);
          //cout <<"buff n= "<< n<< " "<<buff<<endl;
        }
        fclose(hfile);

        //read second part index.html


      }
      else if(message.find("GET")!= -1 )
      {
        FILE * hfile;
        hfile = fopen("header_2", "w");
        //writing to file

        n = read(sockfd,buffer,255);
        fputs(buffer, hfile);
        //cout << "n = "<< n<<endl;

        buff = buffer;
        cout << buff;
        //cout <<"buff n= "<< n<< " "<<buff<<endl;
        bzero(buffer,256);
        n = read(sockfd,buffer,207);
        buff = buffer;
        cout <<buff ;
        fputs(buffer, hfile);
        /*while(n>0)
        {
          fputs(buffer, hfile);

          //cout <<"buff n= "<< n<< " "<<buff<<endl;
          bzero(buffer,256);
          n = read(sockfd,buffer,255);
          buff = buffer;
          cout <<"buff n= "<< n<< " "<<buff<<endl;
        }*/

        fclose(hfile);
        //cout << "Done with header_2 "<<endl;
        FILE * pfile;

        //read second part index.html
        /*int pos_file = message.find("/");
        pos_file=pos_file+1;//skipping /
        int pos_html = message.find(".html")+5;
        string file_name = message.substr(pos_file,pos_html);*/

        //buffer = file_name.c_str();

        pfile = fopen("index_2.html","w");
        if(pfile != NULL)
        {
          read(sockfd,buffer,255);

          while(n>0)
          {
            fputs(buffer, hfile);
            buff = buffer;
            cout <<buffer;
            //cout <<"buff n= "<< n<< " "<<buff<<endl;
            bzero(buffer,256);
            n = read(sockfd,buffer,255);
            //cout <<"buff n= "<< n<< " "<<buff<<endl;
          }

          //cout <<buff;
        }
        fclose(pfile);


      }//end of get


      /* Wait for response from the server */

      if (n < 0)  {
          fprintf(stderr, "Error reading from socket, errno = %d (%s) \n",
                  errno, strerror(errno));
          return -1;
      }
    }// end of get and head
    else if(message.find("POST")!= -1 )
    {

      n = read(sockfd, buffer, 255);
      string buff(buffer);

      //cout << buff<<endl;
      //cout <<"In post"<<endl;
      int post_file_first=0;
      post_file_first = message.find("POST /")+6;
      string filename;
      int post_file_end = message.find(".html");
      filename = message.substr(post_file_first,post_file_end);
      // open file name and transmit
      fstream file;
      file.open ("index.html", fstream::in );
      string out;

      while(!file.eof())
      {
        getline(file,out);
        out.append("\n");
        //cout<<"sending: "<<out<<endl;
        write(sockfd,out.c_str(),out.length());
        out ="";
      }
      file.close();
      close(sockfd);
      //cout <<filename <<endl;
    }


    /* Display server response */
    printf("%s\n",buffer);

    close(sockfd);

    return 0;
}
