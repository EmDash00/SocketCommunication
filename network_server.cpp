//Networking Libraries
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

//Debug info
#include <iostream>

//Error processing
#include <errno.h>


//C++ strings
#include <string.h>



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>



#define INVALID -1 //All instances of "INVALID" will be replaced with -1 at runtime


typedef int Socket; //Now I can use Socket anywhere I'd use int. Useful because sockets are described by integers.

void* get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main()
{	
	int status;

	addrinfo hints;
	addrinfo* serverInfo; 

	sockaddr_storage acceptInfo; //sockaddr_storage is a larger beefier version of sockaddr capable of storing any address type. It's casted to sockaddr later. Neat.
	socklen_t client_len = sizeof(acceptInfo);

	Socket mySocket;
	Socket commSocket;


	

	/*

	About the 
	void perror(const char* s)
	char* strerror(int errnum)
	
	functions.

	perror prints an error message into the console. Just feed it a C string.

	strerror gives you the error message string without printing the error provided the error code. The error code is the number returned by some function that has errored.

	We usually pass strerror() errno, which most functions will set before they return on error. 
	
	
	*/
	memset(&hints, 0, sizeof(hints)); //Make sure the memory at where hints is stored is clear.	

	hints.ai_family = AF_UNSPEC; //Can be IPv4 or IPv6. AF_INET is IPv4 only. AF_INET6 is IPv6 only.
	hints.ai_socktype = SOCK_STREAM; //We want a TCP stream socket. This is typically what you want.
	hints.ai_flags = AI_PASSIVE; //Use this if you want to use the "hints" object in a "bind" function call.

	//		const char* node, const char* port, addrinfo* hints, addrinfo** res

	status = getaddrinfo(NULL, "25566", &hints, &serverInfo); //fills servinfo with a bunch of useful info. 

	//The node is what we're connecting to. We're a server, so we're not connecting to anything.

		
	if (status != 0)
	{
		std::cout << "getaddrinfo error: " << gai_strerror(status) << std::endl;	
		return 1;

	}
	
	mySocket = socket(serverInfo->ai_family, serverInfo->ai_socktype, serverInfo->ai_protocol); //Create the socket.


	int yes = '1';
	//		int socket, int option level, int option name, const void* option value, socklen_t option length	
	if (setsockopt(mySocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) 
	{
		//setsockop sets a socket option. When we close the program port 25566 is still open and cannot be used under default options. Changing this socket option allows us to reuse it.
		//If the function returns -1, it means setsockopt failed.
		perror("setsockopt");
		return 1;
	}
	
	bind(mySocket, serverInfo->ai_addr, serverInfo->ai_addrlen); //Usually the computer just randomly assigns an available port, but as a server, we need to know the port number to give clients
	
	freeaddrinfo(serverInfo);

	//listen(Socket socket, int backlog)
	//Backlog is the number of devices allowed in a queuing area where they wait to be accepted.
	while(true)
	{
		if (listen(mySocket, 10) == INVALID)
		{
			perror("listen");
			return 1;
		}
	
		sockaddr* acceptInfo;
	
		//accept(Socket socket, sockaddr* addr, socklen_t* addr_len)
		commSocket = accept(mySocket, acceptInfo, &client_len);

		if (commSocket == INVALID)
		{
	
			perror("accept");
			return 1;
		}
		
				
		if (acceptInfo->sa_family == AF_INET) 
		{
			char IP[INET_ADDRSTRLEN];
			inet_ntop(acceptInfo->sa_family, get_in_addr(acceptInfo), IP, sizeof(IP));
	
			std::cout << "Connection established to: " << IP << std::endl;

			if (strcmp(IP, "127.0.0.1") == 0) //IPs aka "localhost." 
			{
		
				break;
			}

		}
		else
		{	
			char IP[INET6_ADDRSTRLEN];
			inet_ntop(acceptInfo->sa_family, get_in_addr(acceptInfo), IP, sizeof(IP));
	
			std::cout << "Connection established to: " << IP << std::endl;

			if (strcmp(IP, "0:0:0:0:0:0:0:1") == 0) //IPs aka "localhost." 
			{
				break;
			}
		}					
		

	}	
	const char test[] = "Hello other world.";
	
	
	int sendStatus = send(commSocket, test, sizeof(test), 0);
	
	std::cout << "Sent " << sendStatus << " bytes out of " << sizeof(test) << " bytes" << std::endl;

	close(commSocket);
	close(mySocket);
	

	//Before you accept the client's socket is not associated with the server's IP.

	
	/*
		Correct sequence of functions for servers:

		getaddrinfo();
		socket();
		bind();
		listen();
		accept();

	*/


	char exit;

	std::cout << "Press the \"ESC\" key to exit at anytime and enter to exit. Press enter alone to search for new connections." << std::endl;	
	while 	(exit != 27) //ESC character has a ASCII base ten value of 27.
	{	
		
		std::cin >> exit;
		
	}
	

	
		
	return 0;
}




