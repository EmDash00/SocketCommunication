#include "client.h"

client::client(const char* IP, const char* port)
{
	std::cout << "Client constructor started.\n" << std::flush;
	
	memset(&hints, 0, sizeof(hints));

	hints.ai_family = AF_UNSPEC; 
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE; 

	std::cout << "Getting possible server information values...\n" << std::flush;

	do
	{
		status = getaddrinfo(IP, port, &hints, &serverInfo);

		if (status < 0)
		{
			if (errno  == EAI_AGAIN)
			{
				
				continue;
			}
			else 
			{

			std::cout << "getaddrinfo error: " << gai_strerror(status) << "\n" << std::flush;	
			exit(EXIT_FAILURE);
		
			}
		
		}
		
  
	}while(status != 0);

	std::cout << "Acquired possible server information values.\n" << std::flush;

	std::cout << "Attempting to create connection socket...\n" << std::flush;

	for (addrinfo* p = serverInfo; p != nullptr; p = p->ai_next)
	{

		connection = socket(serverInfo->ai_family, serverInfo->ai_socktype, serverInfo->ai_protocol);
		if (connection == INVALID)
		{
			perror("connection socket");
			std::cout << "Trying next available configuration...\n" << std::flush;
	
			continue;
	

		}
	
		std::cout << "Succesfully created a connection socket.\n" << std::flush;  

		break;
	
	}	

	if(serverInfo->ai_family == AF_INET)
	{	
		std::cout << "Attempting to connect to server: " << IP << ":" << port << " through connection socket\n" << std::flush;
	}
	else if(serverInfo->ai_family == AF_INET6)
	{
		
		std::cout << "Attempting to connect to server: [" << IP << "]:" << port << " through connection socket\n" << std::flush;
			
	}

	do
	{
		status = connect(connection, serverInfo->ai_addr, serverInfo->ai_addrlen);
		if (status == INVALID)
		{
			if (errno == EAGAIN || errno == ETIMEDOUT)
			{
				continue;
			}
			else
			{
				perror("connect");
				exit(EXIT_FAILURE);
			}

		}
		
	}while(status != 0);

	if(serverInfo->ai_family == AF_INET)
	{	
		std::cout << "Connection established to server: " << IP << ":" << port << " through connection socket\n" << std::flush;
	}
	else if(serverInfo->ai_family == AF_INET6)
	{
		
		std::cout << "Connection established server: [" << IP << "]:" << port << " through connection socket\n" << std::flush;
			
	}

	std::cout << "Client constructor finished.\n" << std::flush;

	
}

int client::sendall(Socket sock, const char* msg, int* len)
{
	int total_Sent = 0;
	int bytes_Left = *len;
	int bytes_Sent = 0;

	char buf;

	std::cout << "Attempting to send " << *len << " bytes of information.\n" << std::flush;

	while(total_Sent < *len)
	{	
		
		bytes_Sent = send(sock, (msg + bytes_Sent), bytes_Left, 0);
		
		if(bytes_Sent == INVALID)
		{
			
			if (errno == EPIPE)
			{
				std::cout << "Server has closed connection on their end. Send aborted. Closing socket...\n" << std::flush;

			}
			
			{

				perror("send");

			}
			break;
		} 

		total_Sent += bytes_Sent;
		bytes_Left -= bytes_Sent;
	}

	send(sock, terminator, 1, 0);


	std::cout << "Sent " << total_Sent << " bytes out of " << *len << " bytes.\n" << std::flush;

	*len = bytes_Sent;	

	return (bytes_Sent == INVALID) ? -1 : 0;


}

std::string client::recvall(Socket sock)
{
	std::string msg;
	char* temp = new char();
	std::cout << "Awaiting transmission...\n" << std::flush;

	while(true)
	{	
		static bool transmitting = false;
		//std::this_thread::sleep_for(std::chrono::milliseconds(500));

		status = recv(sock, temp, 1, 0);

		if (status != INVALID)
		{	

			if (!transmitting)
			{
				std::cout << "Tranmissiong beginning.\n" << std::flush;		
				transmitting = true;
			}	

			std::string tempString(temp);
			msg += tempString;
			
			//std::cout << msg.at(msg.length()) << std::endl;
			std::cout << "Appended 1 byte..." << std::endl;	
			std::cout << temp << "\n" << std::flush;
			if (tempString == "`")
			{

				std::cout << "Termination character detected. All packets received.\n" << std::flush;
				msg.pop_back();	
				break;	
			}

		}
		else
		{
			perror("recvall");
			exit(EXIT_FAILURE);
		}

			
	
	}
	delete(temp);
	return msg;
	
}

client::~client()
{




}
