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
    cout <<buff<<endl;
    int keep_alive = buff.find("keep-alive");
    string response;
    response ="";

    if(buff.find("HTTP/1.0") != -1)
    {

      //if the command is get, post,
      if(command=="GET")
      {
        //lets find dash
        int slash_pos = buff.find("/");
        int http_pos =  buff.find("HTTP/1.0")+4;
        fstream file;
        if (slash_pos != http_pos)
        {
          cout << slash_pos << " " << http_pos<<endl;
          response ="HTTP/1.0 200 OK GET\n";
          write(sockfd,response.c_str(),response.length());

          file.open ("header", fstream::in );

          string out;
          while(!file.eof())//reading file
          {
            getline(file,out);
            out.append("\n");
            cout<<"sending: "<<out<<endl;
            write(sockfd,out.c_str(),out.length());
            out ="";
          }

          file.close();
          out="\r\n";

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
          if(file!=NULL)
          {

          }
          write(sockfd,out.c_str(), out.length());
          out="";
          while(!file.eof())//reading file
          {
            getline(file,out);//read line and then send out
            out.append("\n");
            write(sockfd,out.c_str(), out.length());
            out="";
          }
          response = "\r\n\r\n";
          write(sockfd, response.c_str(),response.length());
          file.close();
          cout <<"finished sending data"<<endl;
          if(keep_alive < 0)
          {
            close(sockfd);//closing connection
          }


        }
        else
        {
          response = "HTTP/1.0 400\r\n\r\n";
          write(sockfd, response.c_str(),response.length());
          close(sockfd);//closing connection
        }


      }
      else if(command == "POST")
      {
        //response ="POST COMMAND\n";


        unsigned pos = buff.find("/");
        unsigned posend = buff.find(".html");

        string file_name ="copy_";
        file_name += buff.substr(pos+1,posend);//file to be save as



        write(sockfd,file_name.c_str(), file_name.length());


        FILE * pfile;
        pfile = fopen(file_name.c_str(), "w");

        if(pfile != NULL)
        {
          read(sockfd,buffer,255);
          while(n>0)
          {
            fputs(buffer, pfile);
            buff = buffer;
            //cout <<"buff n= "<< n<< " "<<buff<<endl;
            bzero(buffer,256);
            n = read(sockfd,buffer,255);
            //cout <<"buff n= "<< n<< " "<<buff<<endl;
          }
        }
        fclose(pfile);



        response = "\r\n\r\n";
        write(sockfd,response.c_str(), response.length());
        cout <<"Closing "<<endl;
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
              cout<<"sending: "<<response<<endl;
              write(sockfd,response.c_str(),response.length());
              response ="";
            }
        }
        //closing socket
        response = "\r\n\r\n";
        write(sockfd,response.c_str(),response.length() );
        //close(sockfd);
        //closing file reader
        head.close();
      }
      else
      {
        response ="HTTP/1.0 404\r\n\r\n";
        write(sockfd,response.c_str(),response.length() );
        close(sockfd);
      }
    }
    else
    {
      response = "HTTP/1.0 400\r\n\r\n";
      write(sockfd,response.c_str(),response.length() );
      close(sockfd);
      cout<<"bad request 1.0"<<endl;
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
    cout <<"last line" <<endl;

    /*if(keep_alive < 0)
    {
      response = "HTTP/1.0 400\r\n\r\n";
      write(sockfd,response.c_str(),response.length() );
      close(sockfd);//closing connection
    }*/
    response = "HTTP/1.0 400\r\n\r\n";
    write(sockfd,response.c_str(),response.length() );
    close(sockfd);//closing connection

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
