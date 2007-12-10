/*
 *  NetworkThread.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 16.04.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef NETWORK_THREAD_H
#define NETWORK_THREAD_H

#include <iostream>
#include <map>

#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

#include <QtGui/QWidget>


#include "SDL/SDL.h"
#include "SDL_net/SDL_net.h"

#include "MainWindow.h"
#include "ClientSocketList.h"

namespace TestServer  {

	class NetworkThread : public QObject {
		private:
			Q_OBJECT
			
			MainWindow* mainWin;
			
			int port;
			
			IPaddress ip;
			TCPsocket sd;
			
			ClientSocketList* clientSocketList;
			//std::vector<TCPsocket*> clientVector;
			
		public:
			NetworkThread(MainWindow* mainWin, int port);
			~NetworkThread();
			
			void initNetwork();
			
			void run();
			void __run__();
			
			ClientSocketList* getClientSocketList();
		
		signals:
			void testSignal();
			void intSignal(int);
			void newNetworkConnection(QString);
	};
}

#endif