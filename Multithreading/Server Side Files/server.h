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


//Multithreading
#include <pthread.h>
#include <thread>
#include <future>

//Smart pointers and other stuff
#include <memory>

//C Strings
#include <cstring>


//Other includes
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <chrono>

#include "device.h"




#define NUM_DEVICES 1 //Change the 1 to whatever number of devices you wish to support
#define MAX_REQUESTS 1 //Change the 1 to whatever number of kinds of client requests you need

typedef int Socket; //Now I can use Socket anywhere I'd use int. Useful because sockets are described by integers.


class server
{
	public:

		//Variables
		
		bool end = false; //Set to true to close the server.

		Socket listener;
		Socket unidentified;
	

		//Functions

		int sendall(Socket, const char*, int*);
		std::string recvall(Socket);
		
		void queue();


		server(const char*, device*); //Constructor
		~server(); //Destructor

	private:
		//Data

		device* devices;		

		int status; //Status of various calls like accept()

		//sigaction sa;
	
		addrinfo hints;
		addrinfo* serverInfo;

		sockaddr_storage stg_acceptInfo;
		socklen_t stg_acceptLen;
		sockaddr* acceptInfo;
			
		void* get_in_addr(sockaddr*);
		uint16_t get_in_service(sockaddr*);

		void match(char*, size_t);

		const char* terminator = "`";
		
};





