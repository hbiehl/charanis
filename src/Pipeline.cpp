/*
 *  Pipeline.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 09.08.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#include "Pipeline.h"
// project includes
#include "CharacterDataPackage.h"
#include "PackageQueue.h"
#include "PipelineLayer.h"
#include "PipelineMiddleLayer.h"

namespace Charanis {

//std::vector<PipelineMiddleLayer*> pipelineLayerVec;
	
Pipeline::Pipeline(std::string characterName) {
	std::cout << "Pipeline-Constructor" << std::endl;
	this->characterName = characterName;
}


Pipeline::~Pipeline() {
	std::cout << "DESTRUKTOR PIPELINE " << characterName << "    BEGIN" << std::endl;
	for (int i=0; i<pipelineLayerVec.size(); i++) {
		// Stoppen der Threads (PipelineMiddleLayers)
		CharacterDataPackage* package = new CharacterDataPackage(characterName, 0, 0);
		package->setQuitProgram(true);
		pipelineLayerVec[i]->getInputQueue()->addPriorityPackage(package);
	}
	
	for (int i=0; i<pipelineLayerVec.size(); i++) {
		delete pipelineLayerVec[i]->getInputQueue();
		delete pipelineLayerVec[i];
	}
	
	pipelineLayerVec.clear();
	std::cout << "DESTRUKTOR PIPELINE " << characterName << "    END" << std::endl;
}
		
void Pipeline::addLayer(PipelineMiddleLayer* layer) {
	std::cout << "Pipeline.addLayer(...)" << std::endl;
	pipelineLayerVec.push_back(layer);
}

void Pipeline::addLayer(int position, PipelineMiddleLayer* layer) {
	std::cout << "Pipeline.addLayer("<< position <<", ...)" << std::endl;
	std::vector<PipelineMiddleLayer*>::iterator iter = pipelineLayerVec.begin();
	iter = iter+position;
	pipelineLayerVec.insert(iter, layer);
}

void Pipeline::removeLayer(int position) {
	//TODO
	// Sonderbehandlung beim ersten Layer und beim letzen Layer.
}
		
void Pipeline::createInnerQueues() {
	std::cout << "Pipeline.createInnerQueues() BEGIN" << std::endl;

	for (int i=0; i<(pipelineLayerVec.size()-1); i++) {
		std::cout << "Adding connection " << i << std::endl;
		PipelineLayer* sourceLayer = (PipelineLayer*) pipelineLayerVec[i];
		PipelineLayer* destLayer = (PipelineLayer*) pipelineLayerVec[i+1];
		
		PackageQueue* queue = new PackageQueue(sourceLayer, destLayer);
		sourceLayer->setOutputQueue(queue);
		destLayer->setInputQueue(queue);
	}
	std::cout << "Pipeline.createInnerQueues() END" << std::endl;
}

void Pipeline::setInputQueue(PackageQueue* queue) {
	std::cout << "Pipeline.setInputQueue() BEGIN" << std::endl;
	PipelineMiddleLayer* firstLayer = pipelineLayerVec[0];
	queue->setDestinationLayer((PipelineLayer*) firstLayer);
	firstLayer->setInputQueue(queue);
	std::cout << "Pipeline.setInputQueue() END" << std::endl;
}

void Pipeline::setOutputQueue(PackageQueue* queue) {
	std::cout << "Pipeline.setoutputQueue() BEGIN" << std::endl;
	PipelineMiddleLayer* lastLayer = pipelineLayerVec[pipelineLayerVec.size()-1];
	queue->setSourceLayer((PipelineLayer*) lastLayer);
	lastLayer->setOutputQueue(queue);
	std::cout << "Pipeline.setOutputQueue() END" << std::endl;
}
		
void Pipeline::run() {
	std::cout << "Pipeline.run() BEGIN" << std::endl;
	for (int i=0; i<pipelineLayerVec.size(); i++) {
		pipelineLayerVec[i]->run();
	}
	std::cout << "Pipeline.run() END" << std::endl;
}

} // end of namespace
