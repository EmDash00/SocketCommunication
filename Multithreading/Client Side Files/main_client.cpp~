#include "client.h"

int main()
{
	client JetsonTX1("127.0.0.1", "25566");
	
	while(!JetsonTX1.end)
	{	


		

		
		std::string request = JetsonTX1.recvall(JetsonTX1.connection);
		if (request == "request1")
		{
			
			//Do stuff.
			int* len;
			*len = sizeof("Got it!`");
			JetsonTX1.sendall(JetsonTX1.connection, "Got it!`", len); 

				
		
		}
		 
		

	}

}
