//Networking Libraries
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <string.h>

#include <iostream>

#include <errno.h>

#include <memory>

typedef int Socket;

int main()
{
	int status;

	addrinfo hints;
	addrinfo* serverInfo; 

	Socket mySocket;

	
	memset(&hints, 0, sizeof(hints)); 

	hints.ai_family = AF_UNSPEC; 
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE; 

	status = getaddrinfo("127.0.0.1", "25566", &hints, &serverInfo);

	if (status != 0)
	{
		std::cout << "getaddrinfo error: " << gai_strerror(status) << std::endl;
		return 1;
	}
	
	mySocket = socket(serverInfo->ai_family, serverInfo->ai_socktype, serverInfo->ai_protocol); 

	if (connect(mySocket, serverInfo->ai_addr, serverInfo->ai_addrlen) == -1)
	{
		perror("connect");
		return 1;

	}

	std::cout << "Connected." << std::endl;
	
 	auto world = std::make_unique<char>();

	recv(mySocket, world.get(), 24, 0);

	std::cout << "I got mail. It says: " << std::endl << world.get() << std::endl;  


	world.release();

	return 0;

}


