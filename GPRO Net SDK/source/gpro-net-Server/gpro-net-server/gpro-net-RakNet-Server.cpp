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

	gpro-net-RakNet-Server.cpp
	Source for RakNet server management.
*/

#include "gpro-net/gpro-net-server/gpro-net-RakNet-Server.hpp"


namespace gproNet
{
	cRakNetServer::cRakNetServer()
	{
		RakNet::SocketDescriptor sd(SET_GPRO_SERVER_PORT, 0);
		unsigned short MAX_CLIENTS = 10;

		peer->Startup(MAX_CLIENTS, &sd, 1);
		peer->SetMaximumIncomingConnections(MAX_CLIENTS);
	}

	cRakNetServer::~cRakNetServer()
	{
		peer->Shutdown(0);
	}
	// Description of spatial pose.
	struct sSpatialPose
	{
		float scale[3];     // non-uniform scale
		float rotate[3];    // orientation as Euler angles
		float translate[3]; // translation

		// read from stream
		RakNet::BitStream& Read(RakNet::BitStream& bitstream)
		{
			bitstream.Read(scale[0]);
			bitstream.Read(scale[1]);
			bitstream.Read(scale[2]);
			bitstream.Read(rotate[0]);
			bitstream.Read(rotate[1]);
			bitstream.Read(rotate[2]);
			bitstream.Read(translate[0]);
			bitstream.Read(translate[1]);
			bitstream.Read(translate[2]);
			return bitstream;
		}

		// write to stream
		RakNet::BitStream& Write(RakNet::BitStream& bitstream) const
		{
			bitstream.Write(scale[0]);
			bitstream.Write(scale[1]);
			bitstream.Write(scale[2]);
			bitstream.Write(rotate[0]);
			bitstream.Write(rotate[1]);
			bitstream.Write(rotate[2]);
			bitstream.Write(translate[0]);
			bitstream.Write(translate[1]);
			bitstream.Write(translate[2]);
			return bitstream;
		}
	};
	bool cRakNetServer::ProcessMessage(RakNet::BitStream& bitstream, RakNet::SystemAddress const sender, RakNet::Time const dtSendToReceive, RakNet::MessageID const msgID)
	{
		if (cRakNetManager::ProcessMessage(bitstream, sender, dtSendToReceive, msgID))
			return true;

		// server-specific messages
		switch (msgID)
		{
		case ID_NEW_INCOMING_CONNECTION:
			//printf("A connection is incoming.\n");
			return true;
		case ID_NO_FREE_INCOMING_CONNECTIONS:
			//printf("The server is full.\n");
			return true;
		case ID_DISCONNECTION_NOTIFICATION:
			//printf("A client has disconnected.\n");
			return true;
		case ID_CONNECTION_LOST:
			//printf("A client lost the connection.\n");
			return true;

			// test message
		case ID_GPRO_MESSAGE_COMMON_BEGIN:
		{
			// server receives greeting, print it and send one back
			RakNet::BitStream bitstream_w;
			ReadTest(bitstream);
			WriteTest(bitstream_w, "Hello client from server");
			peer->Send(&bitstream_w, MEDIUM_PRIORITY, UNRELIABLE_SEQUENCED, 0, sender, false);
		}	return true;

		}
		return false;
	}
}