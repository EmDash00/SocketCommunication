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

//Multithreading
#include <pthread.h>
#include <thread>
#include <future>

//Smart pointers and other 
#include <memory>

//C Strings
#include <cstring>

//Other includes
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <chrono>

#define INVALID -1
#define DECABYTE 10 //This is the standard length (that I have decreed) for the buffer size. It is equivalent to 10 characters. Feel free to use it. Or not.

typedef int Socket;

class client
{
	public:
	//Variables	

	bool end = false;

	int status;

	addrinfo hints;
	addrinfo* serverInfo; 

	Socket connection;

	//Functions

	client(const char*, const char*);
	std::string recvall(Socket);
	int sendall(Socket, const char*, int*);
	~client();

	private:
	
		const char* terminator = "`";


};