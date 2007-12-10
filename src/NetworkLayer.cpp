/*
 *  NetworkLayer.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 13.04.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "NetworkLayer.h"
#include "EngineManager.h"


namespace Charanis {

NetworkLayer::NetworkLayer(EngineManager* em) :
PipelineMiddleLayer(em->getDataManager(), "__COMMON__", "NetworkLayer") {
	if (DEBUG) std::cout << "NETWORK_LAYER konstruktor BEGIN" << std::endl;
	engineManager = em;
	if (DEBUG) std::cout << "NETWORK_LAYER konstruktor END" << std::endl;
}

NetworkLayer::~NetworkLayer() {
	if (DEBUG) std::cout << "<<< DESCTRUTOR NetworkLayer >>>" << std::endl;
}


void NetworkLayer::run() {
	std::cout << "NetworkLayer.run()" << "(" << getName() << ")" << std::endl;
	// Start the Thread
	//thread = &boost::thread(boost::bind(&(this->runThread), this));
	thread = &boost::thread(boost::bind(&NetworkLayer::__run__, this));
	// When the Thread has finished - join the thread
	thread->join();
}


void NetworkLayer::__run__() {
	std::cout << "--------------------- Network Layer: Setting up Client-Connection" << std::endl;
	
	
	
	MessageParser parser = MessageParser(engineManager);
	
	IPaddress ip;		/* Server address */
	TCPsocket sd;		/* Socket descriptor */
	//int len;
	char buffer[512];
 

 
	if (SDLNet_Init() < 0) {
		std::cout << "--------------------- SDLNet_Init: " << SDLNet_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}
 
	/* Resolve the host we are connecting to */
	if (SDLNet_ResolveHost(&ip, engineManager->getDataManager()->getConfig()->getHostName().c_str(), engineManager->getDataManager()->getConfig()->getPort())) {
		std::cout << "--------------------- SDLNet_ResolveHost: " << SDLNet_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}
 
	/* Open a connection with the IP provided (listen on the host's port) */
	if (!(sd = SDLNet_TCP_Open(&ip))) {
		std::cout << "--------------------- SDLNet_TCP_Open: " << SDLNet_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}
 
	
	
	
	
	//std::string END_TAG = "</message>";
	std::string END_TAG = "</Package>";
	
	bool quit = false;
	
	unsigned long packageId = 0;
	std::string message = "";
	std::string completeMessage;
	while (!quit) {
		bool messageFinished = false;
		
		completeMessage = "";
		while (!messageFinished) {
			int bytesRead = SDLNet_TCP_Recv(sd, buffer, 512);
			if (bytesRead>0) {
				std::cout << "-------------------------------------"<< std::endl;
				for (int i=0; i<bytesRead; i++) {
					message += buffer[i];
				}
					
				std::cout << "I have received the message " << message << std::endl << "(" << message.size() << ")" << std::endl;
				
				std::string::size_type pos = message.find(END_TAG);
				std::cout << "Position of '</Package>'=" << pos << std::endl;
				
				if (pos!=std::string::npos) {
					completeMessage = message.substr(0, pos + END_TAG.size());
					message = message.substr(pos+END_TAG.size());
					messageFinished = true;
					//quit = true;
					
					packageId++;
			
			
			
					std::cout << "BEFORE PARSING" << std::endl;
					std::vector<Package*>* packageVector = parser.parseXmlMessage(completeMessage);
					std::cout << "AFTER PARSING" << std::endl;
					for (std::vector<Package*>::iterator it = packageVector->begin(); it!=packageVector->end(); it++) {
						Package* package = (*it);
						if (package->getType() == Package::CHARACTER_DATA_PACKAGE_TYPE) {
							CharacterDataPackage* characterPackage = (CharacterDataPackage*) package;
							PackageQueue* outputQueue = getOutputQueue(characterPackage->getCharacterName());
							if (outputQueue!= NULL) {
								outputQueue->addPackage(characterPackage);
								//std::cout << "ADD QUEUE TIME (" << characterPackage->getCharacterName() <<") " << characterPackage->getLength() << std::endl;
								getDataManager()->addQueueTime(characterPackage->getCharacterName(), characterPackage->getLength());
								//std::cout << "DONE ))))))))))" << std::endl;
							} else {
								// TODO: RICHTIGE FEHLERMELDUNG
								std::cerr << "Could not put CharacterDataPackage in proper Queue: the character "+characterPackage->getCharacterName()+" does not exist!!!!" << std::endl;
							}
						} else {//if ( (package->getType() == Package::ADD_CHARACTER_PACKAGE_TYPE)
								//	|| (package->getType() == Package::AMBIENT_LIGHT_PACKAGE_TYPE)
								//	|| (package->getType() == Package::DIRECTIONAL_LIGHT_PACKAGE_TYPE)) {
							std::cout << "*****************************************"<<std::endl;
							std::cout << "Sending Message (not a CharacterDataPackage)" << std::endl;
							std::cout << "*****************************************"<<std::endl;
							engineManager->getRenderingLayer()->getInputQueue()->addPackage(package);
							std::cout << "SENDING DONE " << std::endl;
						}

					}
				}
				
				//if(strcmp(buffer, "quit") == 0) {
				//	quit = true;
				//}
			} else {
				std::cout << "\n\n\nQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ  TCP_RECEIVE FAILED !!!!!\n\n\n"<< std::endl;
				// TODO: close socket!!!
			}
		}
		//std::cout << "============= COMPLETE MESSAGE FOLLOWS =============" << std::endl;
		//std::cout << completeMessage << std::endl;
		//std::cout << "============= NEW MESSAGE FOLLOWS =============" << std::endl;
		//std::cout << message << std::endl;
		
	}

	SDLNet_TCP_Close(sd);
	SDLNet_Quit();
}



void NetworkLayer::setOutputQueue(std::string characterName, PackageQueue* queue) {
	queueMap[characterName] = queue;
}


PackageQueue* NetworkLayer::getOutputQueue(std::string characterName) {
	PackageQueue* queue = NULL;
	if (queueMap.find(characterName) != queueMap.end()) {
		queue = queueMap[characterName];
	}
	return queue;
}

} // end of namespace