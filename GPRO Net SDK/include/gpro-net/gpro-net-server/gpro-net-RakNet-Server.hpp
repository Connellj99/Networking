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

	gpro-net-RakNet-Server.hpp
	Header for RakNet server management.
*/

#ifndef _GPRO_NET_RAKNET_SERVER_HPP_
#define _GPRO_NET_RAKNET_SERVER_HPP_
#ifdef __cplusplus


#include "gpro-net/gpro-net/gpro-net-RakNet.hpp"
#include <vector>


namespace gproNet
{
	// eMessageServer
	//	Enumeration of custom server message identifiers.
	enum eMessageServer
	{
		ID_GPRO_MESSAGE_SERVER_BEGIN = ID_GPRO_MESSAGE_COMMON_END,



		ID_GPRO_MESSAGE_SERVER_END
	};


	// cRakNetServer
	//	RakNet peer management for server.
	class cRakNetServer : public cRakNetManager
	{
		// public methods
	public:
		// cRakNetServer
		//	Default constructor.
		cRakNetServer();

		void masterServerListCreate();

		// ~cRakNetServer
		//	Destructor.
		virtual ~cRakNetServer();

		// protected methods
	protected:
		// ProcessMessage
		//	Unpack and process packet message.
		//		param bitstream: packet data in bitstream
		//		param dtSendToReceive: locally-adjusted time difference from sender to receiver
		//		param msgID: message identifier
		//		return: was message processed
		virtual bool ProcessMessage(RakNet::BitStream& bitstream, RakNet::SystemAddress const sender, RakNet::Time const dtSendToReceive, RakNet::MessageID const msgID);
		//list of servers v
		unsigned short MAX_SERVERS = 10;
		bool isMasterServer;
		std::vector<cRakNetServer> serverList;
		char SERVER_IP[16] = "127.0.0.1"; //this one would be changed based on the other server's value 
		char MASTER_IP[16] = "127.0.0.1";


	};

}


#endif	// __cplusplus
#endif	// !_GPRO_NET_RAKNET_SERVER_HPP_