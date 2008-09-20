/*
 *  PipelineLayer.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 01.04.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "PipelineLayer.h"
// std includes
#include <iostream>
// dependency includes
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
// project includes
#include "PackageQueue.h"

namespace Charanis {

PipelineLayer::PipelineLayer(DataManager* dm, std::string name) {
	std::cout << "PipelinLayer::PipelineLayer(..., " << name << ")" << std::endl;
	this->dataManager = dm;
	this->name = name;
	
	inputQueue = NULL;
	outputQueue = NULL;
	std::cout << "PipelinLayer " << name << " created" << std::endl;
}
		
PipelineLayer::~PipelineLayer() {
	std::cout << "!!! Destructor PipelineLayer (" << name << ") - BEGIN !!!" << std::endl;
	if (inputQueue != NULL) {
		inputQueue->setDestinationLayer(NULL);
	}
	if (outputQueue != NULL) {
		outputQueue->setSourceLayer(NULL);
	}
	
	std::cout << "!!! Destructor PipelineLayer (" << name << ") - END !!!" << std::endl;
}
		


std::string PipelineLayer::getName() {
	return name;
}


PackageQueue* PipelineLayer::getInputQueue() { 
	return inputQueue; 
}


PackageQueue* PipelineLayer::getOutputQueue() {
	return outputQueue;
}
		

void PipelineLayer::setInputQueue(PackageQueue* queue) {
	inputQueue = queue;
}


void PipelineLayer::setOutputQueue(PackageQueue* queue) {
	outputQueue = queue;
}


DataManager* PipelineLayer::getDataManager() {
	return dataManager;
}

void PipelineLayer::run() {
	std::cout << "<<<<< PipelineLayer.run()" << "  (" << getName() << ") >>>>>" << std::endl;
}

} // end of namespace
