/*
AUTHOR: Abhijeet Rastogi (http://www.google.com/profiles/abhijeet.1989)

This is a very simple HTTP server. Default port is 10000 and ROOT for the server is your current working directory..

You can provide command line arguments like:- $./a.aout -p [port] -r [path]

for ex. 
$./a.out -p 50000 -r /home/
to start a server at port 50000 with root directory as "/home"

$./a.out -r /home/shadyabhi
starts the server at port 10000 with ROOT as /home/shadyabhi

*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<signal.h>
#include<fcntl.h>

#define CONNMAX 1000
#define BYTES 1024

/*set root to tmp, you can change it to your liking*/
char *ROOT = "~/tmp/";
int listenfd, clients[CONNMAX];

char *PORT = "10000";

typedef unsigned int socklen_t;
struct sockaddr {
	unsigned short    sa_family;    // address family, AF_xxx
	char              sa_data[14];  // 14 bytes of protocol address
}; 

struct addrinfo{
	int ai_flags;
	int ai_family;
	int ai_socktype;
	int ai_protocol;
	socklen_t ai_addrlen;
	struct sockaddr *ai_addr;
	char *ai_canonname;
	struct addrinfo *ai_next;
};


/***************************************/
/***************************************/
/*************Function declarations*****/
/***************************************/
/***************************************/
void error(char *);
void startServer(char *);
void respond(int);



int main(int argc, char* argv[])
{

	struct sockaddr_in clientaddr;
	socklen_t addrlen;
	char c;    
	
	int slot=0;
	
	// Setting all elements ie clients to -1: signifies there is no client connected
	int i;
	for (i=0; i<CONNMAX; i++)
		clients[i]=-1;

	//starting up server::
	startServer(PORT);

	// ACCEPT connections until shutdown
	while (1)
	{	
		/*TODO: implement accept syscall,*/
		addrlen = sizeof(clientaddr);
		clients[slot] = accept (listenfd, (struct sockaddr *) &clientaddr, &addrlen);


		if (clients[slot]<0)
			error ("accept() error");
		else
		{
			if ( fork()==0 )
			{
				respond(slot);
				exit(0);
			}
		}

		while (clients[slot]!=-1) slot = (slot+1)%CONNMAX;
	}

	return 0;
}

//start server
void startServer(char *port)
{
	struct addrinfo hints, *res, *p;

	// getaddrinfo for host
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	if (getaddrinfo( NULL, port, &hints, &res) != 0)
	{
		perror ("getaddrinfo() error");
		exit(1);
	}
	// socket and bind
	for (p = res; p!=NULL; p=p->ai_next)
	{	
		/*implement socket syscall*/
		listenfd = socket (p->ai_family, p->ai_socktype, 0);
		/*check if socket succeded*/
		if (listenfd == -1) continue;
		if (bind(listenfd, p->ai_addr, p->ai_addrlen) == 0) break;
	}
	
	if (p==NULL)
	{
		perror ("socket() or bind()");
		exit(1);
	}

	/*freeaddrinfo and getaddrinfo NEED to be implemented somehow, FIXME later*/
	freeaddrinfo(res);

	// listen for incoming connections
	if ( listen (listenfd, 1000000) != 0 )
	{
		perror("listen() error");
		exit(1);
	}
}

//client connection
void respond(int n)
{
	char mesg[99999], *reqline[3], data_to_send[BYTES], path[99999];
	int rcvd, fd, bytes_read;

	memset( (void*)mesg, (int)'\0', 99999 );

	rcvd=recv(clients[n], mesg, 99999, 0);

	if (rcvd<0)    // receive error
		puts("recv() error\n");
	else if (rcvd==0)    // receive socket closed
		puts("Client disconnected upexpectedly.\n");
	else    // message received
	{
		puts(&mesg);
		reqline[0] = strtok (mesg, " \t\n");
		if ( strncmp(reqline[0], "GET\0", 4)==0 )
		{
			reqline[1] = strtok (NULL, " \t");
			reqline[2] = strtok (NULL, " \t\n");
			if ( strncmp( reqline[2], "HTTP/1.0", 8)!=0 && strncmp( reqline[2], "HTTP/1.1", 8)!=0 )
			{
				write(clients[n], "HTTP/1.0 400 Bad Request\n", 25);
			}
			else
			{
				if ( strncmp(reqline[1], "/\0", 2)==0 )
					reqline[1] = "/index.html";        //Because if no file is specified, index.html will be opened by default (like it happens in APACHE...

				strcpy(path, ROOT);
				strcpy(&path[strlen(ROOT)], reqline[1]);
				printf("file: %s\n", path);

				if ( (fd=open(path, O_RDONLY))!=-1 )    //FILE FOUND
				{
					send(clients[n], "HTTP/1.0 200 OK\n\n", 17, 0);
					while ( (bytes_read=read(fd, data_to_send, BYTES))>0 )
						write (clients[n], data_to_send, bytes_read);
				}
				else    write(clients[n], "HTTP/1.0 404 Not Found\n", 23); //FILE NOT FOUND
			}
		}
	}

	/*TODO implement shutdown syscall*/
	shutdown (clients[n], SHUT_RDWR);         //All further send and recieve operations are DISABLED...
	close(clients[n]);
	clients[n]=-1;
}
