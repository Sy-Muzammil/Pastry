#include<iostream>
#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
#include<string>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h> 
#include<unistd.h> 
#define MAX 3
using namespace std;
int count=0;
pthread_t threads[1000000];

typedef struct node
{
	int nodeId;
	int RoutingTable[1000][1000];
	int leaf[2][100000];
	int neighbourset[1000000];
}node;

void join(int port)
{
	int socket_descriptor , network_sd , client_size;
    struct sockaddr_in server , client;
    char *recieving=(char *)malloc(MAX*sizeof(char));
    char *cli_addr=(char *)malloc(MAX*sizeof(char));
    char *option=(char *)malloc(MAX*sizeof(char));
    string path;
  
		
    socket_descriptor = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_descriptor < 0)
    {
        printf("Unable to create socket\n");
        return;
    }
   // puts("Waiting\n");
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);
     
    if( bind(socket_descriptor,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        printf("Unable to bind\n");
        return;
    }
    listen(socket_descriptor ,5);
    client_size = sizeof(struct sockaddr_in);
    network_sd = accept(socket_descriptor, (struct sockaddr *)&client, (socklen_t*)&client_size);
    if (network_sd < 0)
    {
        printf("Unable to accept the request\n");
        return;
    }
}

char * readcmd()
{
	ssize_t line1;
	size_t size;
	char *input;
	line1=getline(&input,&size,stdin);
	if(line1==-1)
	{
		printf("\nUnable to read");
	}
	return input; 
}
void *init(void *threadid)
{
	long *t=(long *)threadid;
	long  tid=*t;
	cout<<"Do Initiolization\n";
	cout<<"Hello tid:"<<tid<<endl;
	pthread_exit(NULL);
	
}
void create()
{
	int rc;
	cout<<"creating thread : "<<count<<endl;
	rc=pthread_create(&threads[count],NULL,init,&count);
	pthread_join(threads[count],NULL);
	if(rc)
	{
		cout<<"fail"<<endl;
		exit(-1);
	}
	count++;
}
void parser(char *cmd)
{
	if(strncmp("create",cmd,6) == 0) 
	{
		create();
	}
	else if(strncmp("port",cmd,4) == 0) 
	{
		int found1,n,p;
		string cmd1=cmd;
		string port;
		n=strlen(cmd);
		found1 = cmd1.find(" ");
    	port=cmd1.substr(found1+1,n);
		p=atoi(port.c_str());
		cout<<"Port:"<<p<<endl;
		//port(p);
	}
	else if(strncmp("get",cmd,3) == 0) 
	{
		int found1,n,k;
		string cmd1=cmd;
		string key;
		n=strlen(cmd);
		found1 = cmd1.find(" ");
    	key=cmd1.substr(found1+1,n);
		k=atoi(key.c_str());
		cout<<"Key:"<<k<<endl;
		//get(p);
	}
	else if(strncmp("join",cmd,4) == 0) 
	{
		int found1,found2,n,p,ip;
		string cmd1=cmd;
		string port,addr;
		n=strlen(cmd);
		found1 = cmd1.find(" ");
    	found2 = cmd1.find(" ",found1+1);
    	addr=cmd1.substr(found1+1,found2-found1-1);
    	port=cmd1.substr(found2+1,n);
		p=atoi(port.c_str());
		cout<<"Add:"<<addr<<endl;
		cout<<"Port:"<<p<<endl;
		//join(addr.c_str(),p);
	}
	else if(strncmp("put",cmd,3) == 0) 
	{
		int found1,found2,n,p,ip;
		string cmd1=cmd;
		string key,value;
		n=strlen(cmd);
		found1 = cmd1.find(" ");
    	found2 = cmd1.find(" ",found1+1);
    	key=cmd1.substr(found1+1,found2-found1-1);
    	value=cmd1.substr(found2+1,n);
		//p=atoi(port.c_str());
		cout<<"Add:"<<key<<endl;
		cout<<"Port:"<<value<<endl;
	//	Put(addr.c_str(),p);
	}
	else if(strncmp("lset",cmd,4) == 0) 
	{
		//display_leaf_set();
	}
	else if(strncmp("routetable",cmd,10) == 0) 
	{
		//display_routetable();
	}
	else if(strncmp("nset",cmd,4) == 0) 
	{
		//display_neighbour_set();
	}
} 	
int main()
{
	char *cmd;
	int i;
	while(1)
	{
		cout<<"Pastry$: ";
		cmd=readcmd();
		parser(cmd);
	}
	//for (i=0;i<10;i++)
		//create();
	return 0;
}	