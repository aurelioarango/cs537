/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;

void processHEAD()
{

}
void processPOST()
{

}
void ProcessGET()
{

}

void *cliSvr(void *arg)
{

    int   n, sockfd;
    char  buffer[256];

    bzero(buffer,256);

    sockfd = *(int *)arg;

    /* Wait for request from client */
    n = read(sockfd,buffer,255);
    if (n < 0) {
        fprintf(stderr, "Error reading from socket, errno = %d (%s)\n",
                errno, strerror(errno));
        close(sockfd);
        return NULL;
    }

    //Parse String for GET HEAD or POST
    //find first white space
    string buff(buffer);

    int ws_pos = buff.find(" ");
    string command = buff.substr(0,ws_pos);
    string response;
    response ="";
    if(command=="GET")
    {
      response ="HTTP/1.0 200 OK GET\n";
      write(sockfd,response.c_str(),response.length());
      fstream file;
      file.open ("header", fstream::in );

      string out;
      while(!file.eof())//reading file
      {
        getline(file,out);//read line and then send out
        out.append("\n");
        write(sockfd,out.c_str(), out.length());
      }

      file.close();
      out="";

      //look for the file or default index
      if(buff.find("/index.html") || buff.find(" / "))
      {
        file.open ("index.html", fstream::in );
      }
      else
      {
        unsigned first = buff.find("/");
        //unsigned second = input.find("/",first+1);
        string filename =buff.substr(first+1,first+1);//trying to open a file
        file.open(filename.c_str(),fstream::in);
      }


      while(!file.eof())//reading file
      {
        getline(file,out);//read line and then send out
        out.append("\n");
        write(sockfd,out.c_str(), out.length());
      }
      file.close();
      close(sockfd);//closing connection


    }
    else if(command == "POST")
    {
      //response ="POST COMMAND\n";

      response="Updating...\n";
      unsigned pos = buff.find(" ");
      unsigned posend = buff.find("\n");
      string file_name ="copy";
      file_name += buff.substr(pos+1,posend-3);//file to be save as

      ofstream file;
      string file_contents="start";
      file.open(file_name.c_str());//opening file
      //read and write
      char  read_buffer[256];

      while (file_contents.length() > 1)
      {

        file_contents="";//clear entry
        read(sockfd, read_buffer, 255);//read line
        string str(read_buffer);


        file_contents.append(str);//store in file contents
        str[0] ='\0';//setting to 0
        file<<file_contents;//saving to file
      }
      cout <<"DONE"<<endl;
      file.close();//closing file
      write(sockfd,response.c_str(), response.length());
      close(sockfd);

    }
    else if(command == "HEAD")
    {
      response ="HTTP/1.0 200 OK\r\n";
      //open file rensonse
      //read file and send it
      //

      write(sockfd,response.c_str(),response.length());
      fstream head;
      head.open("header",fstream::in);

      if(head.is_open())
      {
          while(!head.eof())
          {
            getline(head,response);
            response.append("\n");
          }
          write(sockfd,response.c_str(),response.length());
      }
      //closing socket
      close(sockfd);
      //closing file reader
      head.close();
    }
    else
    {
      response ="HTTP/1.0 400\n";
    }


    //if GET WE load file from machine and transmit it
      // Read the file name that we will look
      // if the file is found transmit it
      // Else NO file found send ERROR

    //IF HEAD we only send the HEAD of the file


    //IF IS POST then we save the file


    /*
    printf("Server:: Here is the message: %s\n",buffer);*/

    /* Send response back to the client */

    if (n < 0)  {
        fprintf(stderr, "Error writing to socket, errno = %d (%s)\n",
                errno, strerror(errno));
        close(sockfd);
        return NULL;
    }

    close(sockfd);

    return NULL;

}


int main(int argc, char *argv[])
{
     int sockfd, clisockfd, port;
     socklen_t clilen;
     struct sockaddr_in serv_addr, cli_addr;

     pthread_t  tid;

     if (argc < 2) {
         fprintf(stderr,"Usage: %s <port>\n", argv[0]);
         exit(1);
     }

     /* Open a TCP socket connection */
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) {
        fprintf(stderr, "Error opening socket, errno = %d (%s) \n",
                errno, strerror(errno));
        return -1;
     }

     bzero((char *) &serv_addr, sizeof(serv_addr));
     port = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(port);
     if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
         fprintf(stderr, "Error bind to socket, erron = %d (%s) \n",
                 errno, strerror(errno));
         return -1;
     }

     /* Setup passive listening socket for client connections */
     listen(sockfd, 5);

     /* Wait for incoming socket connection requests */
     while (1) {
         clilen = sizeof(cli_addr);
         clisockfd = accept(sockfd,
                            (struct sockaddr *) &cli_addr,
                            &clilen);

         if (clisockfd < 0) {
             fprintf(stderr, "Error accepting socket connection request, errno = %d (%s) \n",
                     errno, strerror(errno));
             break;
         }

         /* Create thread for client requests/responses */
         pthread_create(&tid, NULL, &cliSvr, (void *)&clisockfd);
     }

     close(sockfd);

     return 0;
}
