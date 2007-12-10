/*
 *  ClientSocketList.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 19.04.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "ClientSocketList.h"



namespace TestServer {

	ClientSocketList::ClientSocketList() {
		std::cout << "WWWWWWWWWWWWWWWWWW ClientSocketList::ClientSocketList" << std::endl;
	}



	ClientSocketList::~ClientSocketList() {
		boost::mutex::scoped_lock lock(socketList_mutex);
		
		for (SocketList::iterator it = clientSockets.begin(); it != clientSockets.end(); it++) {
			TCPsocket clientSocket = (*it);
			SDLNet_TCP_Close(clientSocket);
			//delete clientSocket;
		}
		clientSockets.clear();
	}



	void ClientSocketList::addClient(TCPsocket clientSocket) {
		boost::mutex::scoped_lock lock(socketList_mutex);
		clientSockets.push_back(clientSocket);
		std::cout << "WWWWWWWWWWWWWWWWWWWWWWW Socket added" << std::endl;
	}



	void ClientSocketList::sendToAll(std::string message) {
		boost::mutex::scoped_lock lock(socketList_mutex);
		SocketList closeSockets;
		
		message = "<message>"+ message +"</message>";
		
		for (SocketList::iterator it = clientSockets.begin(); it != clientSockets.end(); it++) {
			TCPsocket clientSocket = (*it);
			int length = message.length() + 1;
			if (SDLNet_TCP_Send(clientSocket, (char*) message.c_str(), length) < length) {
				// something went wrong - close connection!
				closeSockets.push_back(clientSocket);
			}
		}
		
		for (SocketList::iterator it = closeSockets.begin(); it != closeSockets.end(); it++) {
			TCPsocket clientSocket = (*it);
			std::cout << "--------------------------------- Closing Connection to Client" << std::endl;
			emit loggingSignal(QString("<b>[NET]</b> Connection to Client closed!<br>"));
			SDLNet_TCP_Close(clientSocket);
			clientSockets.remove(clientSocket);
		}
		std::cout << "--------------------------------- Number of connected Client: " << clientSockets.size() << std::endl;
		closeSockets.clear();
	}
}