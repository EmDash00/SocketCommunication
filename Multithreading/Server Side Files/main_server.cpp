#include "server.h"



int main()
{
	bool done = false;

	//Declare as many decies as you want here. Just add another bracketed list (don't forget a comma to seperate between each bracketed list).
	device myDevices[NUM_DEVICES] 
	{
		//{std::string IP, std::string alias, std::vector<std::string> requests},
		{"127.0.0.1", "Myself", {"request1", "request2", "request3"}}
	
	};	

	server myServer("25566", myDevices);



	std::thread queue(&server::queue, &myServer);
	
	
	queue.detach();

	//std::this_thread::sleep_for(std::chrono::seconds(10));


	while(!myServer.end)
	{
		/*
		If you know how to do multi-process programs with fork() go ahead and use this zombie reaper. Be sure to declare an sa object though. 

		FYI: Multithreading is preferred to multi-process.

		sa.sa_handler = sigchld_handler;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = SA_RESTART;

		if (sigaction(SIGCHILD, &sa, NULL) == INVALID)
		{

			perror("sigaction");
			exit(EXIT_FAILURE);

		} 
		*/

		//This is a send test.
		if (done == false && myDevices[Me].connection != INVALID)
		{


			std::cout << myDevices[Me].alias << " Is available!\n" << std::flush;
			myServer.sendall(myDevices[Me].connection, myDevices[Me].requests[request1].c_str(), &myDevices[Me].len_requests[request1]);
			std::string msg = myServer.recvall(myDevices[Me].connection);


			
			std::cout << "Acknowledged " << myDevices[Me].alias << "! \"" << msg << "\" is your answer!\n" << std::flush;
	
			
			done = true;
		}
	}
	
				
	return 0;
}



