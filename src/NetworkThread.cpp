/*
 *  NetworkThread.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 16.04.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "NetworkThread.h"


namespace TestServer {

	NetworkThread::NetworkThread(MainWindow* mainWin, int port) 
	: QObject::QObject() {
		this->mainWin = mainWin;
		this->port = port;
		
		clientSocketList = new ClientSocketList();
		
		QObject::connect(this, SIGNAL(newNetworkConnection(QString)), mainWin, SLOT(writeLog(QString)));
		QObject::connect(this, SIGNAL(intSignal(int)), mainWin, SLOT(intSlot(int)));
		
		if (QObject::connect(this, SIGNAL(testSignal(void)), mainWin, SLOT(test(void))))
			std::cout << "Connected" << std::endl;
		else
			std::cout << "Connecting failed" << std::endl;
		
		initNetwork();
	}
	
	NetworkThread::~NetworkThread() {
		// TODO: close all client sockets
		delete clientSocketList;
		
		
		SDLNet_TCP_Close(sd);
		SDLNet_Quit();
	}
			
				
	void NetworkThread::initNetwork() {
		std::cout << "<<<<<<<<<<<<< NetworkThread::initNetwork()" << std::endl;;
		if (SDLNet_Init() < 0) {
			std::cout << "<<<<<<<<<<<<< SDLNet_Init: " << SDLNet_GetError() << std::endl;;
			exit(EXIT_FAILURE);
		}
	 
		/* Resolving the host using NULL make network interface to listen */
		if (SDLNet_ResolveHost(&ip, NULL, port)) {
			std::cout << "<<<<<<<<<<<<< SDLNet_ResolveHost: " << SDLNet_GetError() << std::endl;
			exit(EXIT_FAILURE);
		}
	 
		/* Open a connection with the IP provided (listen on the host's port) */
		if (!(sd = SDLNet_TCP_Open(&ip))) {
			std::cout << "<<<<<<<<<<<<< SDLNet_TCP_Open: " << SDLNet_GetError() << std::endl;
			exit(EXIT_FAILURE);
		}
	}
							
	void NetworkThread::run() {
		boost::thread* thread = &boost::thread(boost::bind(&TestServer::NetworkThread::__run__, this));
		thread->join();
	}
	
	void NetworkThread::__run__() {
		TCPsocket csd;
		IPaddress* remoteIP;
		bool quit = false;
		while (!quit) {
			std::cout << "<<<<<<<<<<<<< Server::waitForConnection() - WAITING..." << std::endl;
			SDL_Delay(1000);
			
			
			//emit testSignal();
			//quit = true;
			/* This check the sd if there is a pending connection.
			* If there is one, accept that, and open a new socket for communicating */
			if ((csd = SDLNet_TCP_Accept(sd))) {
				/* Now we can communicate with the client using csd socket
				* sd will remain opened waiting other connections */
	 
				/* Get the remote address */
				if ((remoteIP = SDLNet_TCP_GetPeerAddress(csd))) {
					/* Print the address, converting in the host format */
					//std::cout << "<<<<<<<<<<<<< Host connected: " <<  SDLNet_Read32(&remoteIP->host) << "    port: " << SDLNet_Read16(&remoteIP->port) << std::endl;
					//std::cout << "<<<<<<<<<<<<< Host connected: " <<  remoteIP->host << "    port: " << remoteIP->port << std::endl;
					//clientVector.push_back(&csd);
					clientSocketList->addClient(csd);
					emit newNetworkConnection("<b>[NET]</b> A new Client connected<br>");
				} else {
					std::cout << "<<<<<<<<<<<<< SDLNet_TCP_GetPeerAddress: " << SDLNet_GetError() << std::endl;
				}
	
				
			}
		}
	}
	
	
	ClientSocketList* NetworkThread::getClientSocketList() {
		return clientSocketList;
	}
}