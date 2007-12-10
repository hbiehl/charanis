/*
 *  EngineManager.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 31.01.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */



#include "EngineManager.h"
#include "NetworkLayer.h"

#include "OpenAL/al.h"
#include "OpenAL/alc.h"
//#include "OpenAL/alut.h" // Problem mit XCode-Update

namespace Charanis {

EngineManager::EngineManager() {
	std::cout << "===== Constructor EngineManager BEGIN ====" << std::endl;
	
	
	
	dataManager = new DataManager();
	
	networkLayer = new NetworkLayer(this);
	renderingLayer = new RenderingLayer(this, dataManager, "../../plugins.cfg", "../../ogre.cfg", "ogre.log");
	PackageQueue* queue = renderingLayer->getInputQueue();
	if (queue == NULL) {
		queue = new PackageQueue(NULL, renderingLayer);
		renderingLayer->setInputQueue(queue);
	}


	pipelineManager = new PipelineManager(dataManager, networkLayer, renderingLayer);


	
	//addCharacter("Robbie", "robot.mesh", Ogre::Vector3(0, -50, 0), Ogre::Vector3(1,0,-1));
	//addCharacter("Herrmann", "robot.mesh", Ogre::Vector3(-80, -50, -40), Ogre::Vector3(1,0,-0.3));
	//addCharacter("Emma", "Mesh.mesh", Ogre::Vector3(-40, -50, 20), Ogre::Vector3(0,-1,0)); // OK
	//std::cout << "IMPORTING FACIAL EXPRESSION FILE" << std::endl;
	//dataManager->getBehaviorLibrary("Robbie")->getExpressionLibrary()->importExpressionFile(config->getFEMLDir(), "test.feml");
	//dataManager->getBehaviorLibrary("Emma")->getExpressionLibrary()->importExpressionFile(config->getFEMLDir(), "test.feml");
	//std::cout << "DONE ......... IMPORTING FACIAL EXPRESSION FILE" << std::endl;
	
	
	
	
	
	std::cout << "INIT..." << std::endl;
	// Init openAL
	//alutInit(0, NULL); // Problem mit XCode-Update
	
	// ----- workaround BEGIN
	ALCdevice* alcDevice = alcOpenDevice(NULL);
	ALCcontext* alcContext = NULL;
	if (alcDevice) { // TODO: do something, if an error occured!
		alcContext = alcCreateContext(alcDevice,NULL); 
		alcMakeContextCurrent(alcContext);
	}
	// ----- workaround END
	
	
	// Clear Error Code (so we can catch any new errors)
	alGetError(); // Problem mit XCode-Update
	
	
		
	networkLayer->run();
	renderingLayer->run();




	std::cout << "Cleaning..." << std::endl;
	//alutExit(); // Problem mit XCode-Update
	
	// ----- workaround BEGIN
	alcMakeContextCurrent(NULL);
	if (alcContext) {
		alcDestroyContext(alcContext); 
	}
	if (alcDevice) {
		alcCloseDevice(alcDevice);
	}
	// ----- workaround END


	std::cout << "===== Constructor EngineManager DONE ====" << std::endl;
}




EngineManager::~EngineManager() {
	std::cout << "===== Destructor EngineManager BEGIN ====" << std::endl;
	
	delete pipelineManager;
	
			
	// TODO: stop networkLayer-Thread
	delete networkLayer;
	
	// TODO: stop renderingLayer-Thread
	delete renderingLayer;
	

	delete dataManager;
	
	//delete config;
	std::cout << "===== Destructor EngineManager DONE ====" << std::endl;
}



/*Config* EngineManager::getConfig() {
	return config;
}*/



DataManager* EngineManager::getDataManager() {
	return dataManager;
}

RenderingLayer* EngineManager::getRenderingLayer() {
	return renderingLayer;
}



void EngineManager::stop() {
	pipelineManager->removeAllCharacterPipelines();
}

/*
void EngineManager::controlCamera(Ogre::Vector3* position, Ogre::Vector3* direction) {
	renderingLayer->getInputQueue()->addPackage(new CameraControlPackage(position, direction));
}
*/


void EngineManager::addCharacter(std::string characterName, std::string mesh, Ogre::Vector3* position, Ogre::Vector3* direction, Ogre::Real scale) {
	pipelineManager->addCharacterPipeline(characterName);
	dataManager->addCharacter(characterName);
	renderingLayer->getInputQueue()->addPackage(new AddCharacterPackage(characterName, mesh, position, direction, scale));
}

void EngineManager::removeCharacter(std::string characterName) {
	pipelineManager->removeCharacterPipeline(characterName);
	//dataManager->removeCharacter(characterName);
	renderingLayer->getInputQueue()->addPackage(new RemoveCharacterPackage(characterName));
}

/*
void EngineManager::addObject(std::string objectName, std::string meshName, Ogre::Vector3* position, Ogre::Quaternion* orientation, Ogre::Real scale) {
	std::cout << "EngineManager::addObject()" << std::endl;
	renderingLayer->getInputQueue()->addPackage(new AddObjectPackage(objectName, meshName, position, orientation, scale));
}

void EngineManager::removeObject(std::string objectName) {
	// TODO: NOT IMPLEMENTED YET!!!
	//std::cout << "EngineManager::removeObject(std::string objectName) IS NOT IMPLEMENTED YET!!!" << std::endl; 
	renderingLayer->getInputQueue()->addPackage(new RemoveObjectPackage(objectName));
}
*/

} // end of namespace