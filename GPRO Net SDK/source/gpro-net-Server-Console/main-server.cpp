/*
   Copyright 2021 Daniel S. Buckstein

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

	   http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/

/*
	GPRO Net SDK: Networking framework.
	By Daniel S. Buckstein

	main-server.cpp
	Main source for console server application.
*/
/*


	For this programming challenge,
	you will propose the design for, and begin prototyping, 
	a master server architecture using the existing course infrastructure.  
	You may do this on your local machine or GRID it is not expected to be fully functional or tested, 
	given the time constraint, but the design must be feasible for use with RakNet and a C++ based framework such as the one provided.

	The master server is the default connection target for any new client.
	It keeps an active record of the available game servers and allows the client to connect to a game. 
	Upon disconnection from a game, the player returns to the master server.


	needs:
	autoconnect to master
	a list of servers
	connection to any selection of servers
	disconnecting from a server
	when disconnecting, bringing back to master


	ideaing
	-pretty much mostly done in server I think
	-must keep track of serveral server IPs, probably using a vector because theyre nice    - pseudoified
	-must include master as the first ip in the list to easily access in case of disconnect / 
	also just store master seperate as a hardcoded server since it won't be changing         - pseudoified
	-give the user a way to select any server from a list, like if the list is all displayed then press a number  -mostly pseudoified
	that corrsponds to the server and take the player input and search for the vector at that input
	-put the player through to that server      - pseudofieid
	-if server loses player connection, automatically connect with master server    -pseudoified

	confusions:
	-how do I use this server to contain multiple servers?
	-its been weeks since I last worked on project 2 and I forget things, I wish I had the ability to access my previous projects 
	-I think I roughly know how to do this I just don't understand how I am meant to track a bunch of servers and a master server
	seperately but also have them all running through this c++ proj (and by roughly I mean in theory, the syntax is eluding my memory)
	I dont know actual implementation and I think I did my best outlining the process so that's all I can do

*/

#include "gpro-net/gpro-net-server/gpro-net-RakNet-Server.hpp"


int main(int const argc, char const* const argv[])
{
	gproNet::cRakNetServer server;

	while (1)
	{
		server.MessageLoop();
	}

	printf("\n\n");
	system("pause");
}
