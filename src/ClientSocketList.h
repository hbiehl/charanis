/*
 *  ClientSocketList.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 19.04.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef CLIENT_SOCKET_LIST_H
#define CLIENT_SOCKET_LIST_H

#include <list>
#include <boost/thread/thread.hpp>
#include <iostream>

#include <QtGui/QWidget>

#include "SDL_net/SDL_net.h"

namespace TestServer {

	class ClientSocketList : public QObject {
		private:
			Q_OBJECT;
			
			boost::mutex socketList_mutex;
			
			typedef std::list<TCPsocket> SocketList;
			SocketList clientSockets;
		
		public:
			ClientSocketList();
			~ClientSocketList();

			void addClient(TCPsocket clientSocket);
			/*void removeClient(TCPsocket* clientSocket);*/
			
			void sendToAll(std::string message);
		
		signals:
			void loggingSignal(QString);

	};
}

#endif