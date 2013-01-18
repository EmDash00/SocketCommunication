//C++ strings
#include <string>

//Nonstatic arrays
#include <vector>

#define INVALID -1 //All instances of "INVALID" will be replaced with -1 at runtime. DO NOT CHANGE.

typedef int Socket; //Now I can use Socket anywhere I'd use int. Useful because sockets are described by integers.

enum num_device //list your devices here
{	
	Me	
};

enum requests_JetsonTX1 //Name your requests here. Add a new enum for each device.
{
	request1,
	request2,
	request3
};

struct device //Declare a vector of devices in the main program to satisfy your needs.
{
							
	Socket connection;

	std::string IP; 
	std::string alias;
	std::vector<std::string> requests;

	std::vector<int> len_requests;

	device(std::string, std::string, std::vector<std::string>);

};
