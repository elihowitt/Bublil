#include"loggerMessages.h"
#include"loggerUtil.h"

#include"net\Client.h"
#include"net\Server.h"

int main()
{
	bool server;
	lg::cwout::sayHello();
	lg::cwout::generalLog("Question", "Open as server?");
	std::cin >> server;
	if (server)
	{
		Server MyServer(1111, false); //Create server on port 1111, false=do not loopback to localhost (others can connect)
		while (true)
		{
			MyServer.ListenForNewConnection(); //Accept new connection (if someones trying to connect)
		}
	}
	else//Client
	{ 
		Client myClient("127.0.0.1", 1111); //Create client to connect to server 127.0.0.1 [localhost] on port 1111
		if (!myClient.Connect()) //If client fails to connect...
		{
			std::cout << "Failed to connect to server..." << std::endl;
			system("pause");
			return -1;
		}
		std::string userinput; //holds the user's chat message
		while (true)
		{
			std::getline(std::cin, userinput); //Get line if user presses enter and fill the buffer
			myClient.SendString(userinput); //Send string to server
		}

	}

	return 0;
}