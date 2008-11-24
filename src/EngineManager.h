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

// std includes
#include <string>
// dependency includes
#include <Ogre/OgrePrerequisites.h>


namespace Ogre {
class Vector3;
} // end of namespace Ogre


namespace Charanis {

class PipelineManager;
class DataManager;
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
		
		
		PipelineManager* pipelineManager;
		
	public:
		EngineManager();
		~EngineManager();
		
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