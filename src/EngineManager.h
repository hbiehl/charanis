/*
 *  EngineManager.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 31.01.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */



#ifndef ENGINGE_MANAGER_H
#define ENGINGE_MANAGER_H


#include <string>


#include "SDL/SDL.h"
#include "Ogre/Ogre.h"

#include "DataManager.h"
#include "Config.h"


//#include "RenderingLayer.h"

#include "AddCharacterPackage.h"
#include "RemoveCharacterPackage.h"
#include "PipelineManager.h"

namespace Charanis {

class RenderingLayer;
class NetworkLayer;


/**
 * \brief Hauptklasse von Charanis zur Verwaltung der verschiedenen Komponenten.
 *
 *
 * Diese Klasse initialisiert und verwaltet die verschiedenen Komponenten von Charanis. Sie stellt
 * damit praktisch die "Schaltzentrale" von Charanis dar.
 *
 * Hier werden der Netzwerk- und der Rendering-Thread gestartet, sowie die Erzeugung neuer Pipelines beim Hinzukommen weiterer Charakatere angestoßen.
 */
class EngineManager {
	private:
		DataManager* dataManager;
		NetworkLayer* networkLayer;
		RenderingLayer* renderingLayer;
		
		//Config* config;
		
		PipelineManager* pipelineManager;
		
	public:
		EngineManager();
		~EngineManager();
		
		//Config* getConfig();
		DataManager* getDataManager();
		RenderingLayer* getRenderingLayer();
		
		void stop();
		
		//void controlCamera(Ogre::Vector3* position, Ogre::Vector3* direction);
		
		void addCharacter(std::string characterName, std::string mesh, Ogre::Vector3* position, Ogre::Vector3* direction, Ogre::Real scale=1);
		void removeCharacter(std::string characterName);
		
		
		//void addObject(std::string objectName, std::string meshName, Ogre::Vector3* position, Ogre::Quaternion* orientation, Ogre::Real scale=1);
		//void removeObject(std::string objectName);
};

} // end of namespace
#endif