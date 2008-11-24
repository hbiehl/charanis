/*
 *  IdleGenerationLayer.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 11.06.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#include "IdleGenerationLayer.h"

// project includes
#include "CharacterDataPackage.h"
#include "DataManager.h"
#include "PackageQueue.h"


namespace Charanis {

void IdleGenerationLayer::handlePackage(Package* package) {
	//std::cout << std::endl << "MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM - IDLE_GERNETATION_LAYER: handlePackage(...) - "<< package->getStartTime() << " - MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM" << std::endl << std::endl;
	//dataManager->addQueueTime(getCharacterName(), package->getLength());
}

void IdleGenerationLayer::noPackageReceived() {
	//std::cout << "IDLE_GENERATION_LAYER 8888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888 NO PACKAGE RECEIVED!!!!!" << std::endl;
	Ogre::Real IDLE_TIME = 2;
	Ogre::Real MINIMAL_FORWARD_TIME=1;
	
	Ogre::Real time = dataManager->getQueueTime(getCharacterName());
	
	if (time < dataManager->getEngineTime() + MINIMAL_FORWARD_TIME) {
		CharacterDataPackage* package = new CharacterDataPackage(getCharacterName(), time, time+IDLE_TIME);
		//package->addCharacterPerformance(new CharacterPerformance(getCharacterName(), "Idle", time, time+IDLE_TIME));
		dataManager->addQueueTime(getCharacterName(), IDLE_TIME);
		
		if (getOutputQueue() != NULL) {
			getOutputQueue()->addPackage(package);
		}
		//std::cout << "8888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888 Idle-Package (" << getCharacterName() <<" / "<<time << ", " << (time+IDLE_TIME) << ") sent!" << std::endl;
	}

}

IdleGenerationLayer::IdleGenerationLayer(DataManager* dm, std::string characterName) : PipelineMiddleLayer(dm, characterName, "IdleGenerationLayer") {
}

} // end of namespace