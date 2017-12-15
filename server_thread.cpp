#include <iostream>
#include <stdio.h>
#include <string.h>    //strlen
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h> 
#include <utility> 
#include <cstdlib>
#include <arpa/inet.h> 
#include <cstddef>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
using namespace std;
//create port_ip_join
int main(int argc, char *argv[])
{
int sockfd, newsockfd, portno;
socklen_t clilen;
char buffer[256],cl_addr[256];
char option[3];
struct sockaddr_in serv_addr,cli_addr;

    if (argc < 2) 
    {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
        }

     /*create socket*/
sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        cout<<"Socket not found"<<endl;

bzero((char *) &serv_addr, sizeof(serv_addr));

/*port no*/
portno = atoi(argv[1]);

serv_addr.sin_family = AF_INET;
serv_addr.sin_addr.s_addr = INADDR_ANY;
serv_addr.sin_port = htons(portno);
    
    /*bind*/
if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
    cout << "Error on Binding"<<endl;
      

      /*listen*/
listen(sockfd,5);
clilen = sizeof(cli_addr);

newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);
    
    if (newsockfd < 0) 
        cout << "ERROR on accept"<<endl;

// reads from the client //
bzero(buffer,256);
    
strcpy(cl_addr,inet_ntoa(cli_addr.sin_addr));

        //whether to search or update//
/*while(read(newsockfd,option,255))
    {
    
        //read(newsockfd,option,255);
        read(newsockfd,buffer,255);
        switch(*option)
        {
            case '1':   search(buffer,newsockfd);
                log_file_search(buffer,cl_addr);
                bzero(buffer,256);
                break;
            case '2':   update_repo(buffer,cl_addr);
                log_file_update(buffer,cl_addr);
                bzero(buffer,256);
                break;
        case '3':       exit(1);            
                break;
        }
bzero(buffer,256);
    }*/

close(newsockfd);

close(sockfd);
return 0; 
}