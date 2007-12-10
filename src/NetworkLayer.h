/*
 *  NetworkLayer.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 13.04.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef NETWORK_LAYER_H
#define NETWORK_LAYER_H


#include <SDL/SDL.h>
#include <SDL_net/SDL_net.h>

#include <Ogre/Ogre.h>

#include "MessageParser.h"
#include "PipelineMiddleLayer.h"
#include "CharacterDataPackage.h"

#include "DataManager.h"

namespace Charanis {

class EngineManager;

typedef std::map<std::string, PackageQueue*> QueueMap;

/**
 * \brief Die Netzwerkschicht von %Charanis.
 *
 * Hier wird die Verbindung zur Storytelling-Plattform hergestellt. Eingehende Nachrichten werden entgegengenommen
 * und an den MessageParser übergeben. 
 */
class NetworkLayer : public PipelineMiddleLayer {
	private:
		static const bool DEBUG = false;
		//Ogre::Real time;
		QueueMap queueMap;
		EngineManager* engineManager;
	
	public:
		NetworkLayer(EngineManager* em);
		~NetworkLayer();
		
		void run();
		void __run__();
		
		void setOutputQueue(std::string characterName, PackageQueue* queue);
		PackageQueue* getOutputQueue(std::string characterName);
};

} // end of namespace

#endif