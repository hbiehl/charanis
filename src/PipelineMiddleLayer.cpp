/*
 *  PipelineMiddleLayer.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 23.04.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "PipelineMiddleLayer.h"

namespace Charanis {


PipelineMiddleLayer::PipelineMiddleLayer(DataManager* dm, std::string characterName, std::string layerName) 
: PipelineLayer::PipelineLayer(dm, layerName) {
	std::cout << "PipelineMiddleLayer::PipelineMiddleLayer"<< std::endl;
	this->characterName = characterName;
}


PipelineMiddleLayer::~PipelineMiddleLayer() {
	std::cout << "§§§ DESCTRUTOR PipelineMiddleLayer "<< getName() << "/" << characterName << " BEGIN §§§" << std::endl;
	boost::mutex::scoped_lock lock(thread_mutex);
	//std::cout << layerName << "/" << characterName << "   deleting InputQueue" << std::endl;
	/*
	if (getInputQueue() != NULL) {
		delete inputQueue;
		inputQueue = NULL;
	}
	*/
	std::cout << "§§§ DESCTRUTOR PipelineMiddleLayer " << getName() << "/" << characterName << " END §§§" << std::endl;
}


void PipelineMiddleLayer::run() {
	std::cout << "PipelineMiddleLayer.run()" << "(" << getName() << ")" << std::endl;
	boost::mutex::scoped_lock lock(thread_mutex);

	// Start the Thread
	//thread = &boost::thread(boost::bind(&(this->runThread), this));
	thread = &boost::thread(boost::bind(&PipelineMiddleLayer::__run__, this));
	std::cout << "THREAD " << getName() << "/" << characterName << " IS FINISHED" << std::endl;
	// When the Thread has finished - join the thread
	thread->join();
	//threadFinished_condition.notify_one();
}

void PipelineMiddleLayer::__run__() {
	bool quit = false;
	while (!quit) {
		
		if (getInputQueue() != NULL) {
			Package* package = getInputQueue()->getPackage();
			if (package != NULL) {
				handlePackage(package);
				
				/*
				if (package->getQuitProgram()) {
					quit = true;
				}
				*/
				if (getOutputQueue() != NULL) {
					getOutputQueue()->addPackage(package);
				} else {
					std::cout << "Layer " << getName() << ": End of Queue has been reached!!!" << std::endl;
					// package is not needed any more and has to be deleted now
					delete package;
				}
			} else { // => inputQueue is emtpy
				noPackageReceived();
			}
		}
	}
}


void PipelineMiddleLayer::handlePackage(Package* package) {
	std::cout << "Layer " << getName() << ": Package received (PackageType=" << package->getType() << ")" << std::endl;
}

void PipelineMiddleLayer::noPackageReceived() {
	//std::cout << "Layer " << getName() << ": InputQueue is empty - noPackageReceived()" << std::endl;
}



std::string PipelineMiddleLayer::getCharacterName() {
	return characterName;
}

} // end of namespace