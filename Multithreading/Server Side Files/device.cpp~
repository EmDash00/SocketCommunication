#include "device.h"

device::device(std::string init_IP, std::string init_alias, std::vector<std::string> init_requests)
{

				
	connection = INVALID;
	IP = init_IP;
	alias = init_alias;
	requests = init_requests;

	

	for(std::vector<std::string>::iterator iter = requests.begin(); iter != requests.end(); iter++)
	{

		len_requests.push_back(iter->length());	
	}
				

}
