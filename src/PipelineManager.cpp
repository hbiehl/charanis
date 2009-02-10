/*
 *  PipelineManager.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 01.04.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#include "PipelineManager.h"

// project includes
#include "AnimationCutterLayer.h"
#include "AnimationGenerationLayer.h"
#include "IdleGenerationLayer.h"
#include "NetworkLayer.h"
#include "PackageQueue.h"
#include "Pipeline.h"
#include "RenderingLayer.h"


namespace Charanis {

PipelineManager::PipelineManager(DataManager* dm, NetworkLayer* nl, RenderingLayer* rl) {
	this->dataManager = dm;
	this->networkLayer = nl;
	this->renderingLayer = rl;
}


PipelineManager::~PipelineManager() {
	std::cout << "===== Destructor PipelineManager BEGIN ====" << std::endl;
	
	for (PipelineMap::iterator it = pipelineMap.begin(); it!=pipelineMap.end(); it++) {
		// TODO: stop Pipeline
		delete it->second;
	}
	pipelineMap.clear();
	
	std::cout << "===== Destructor PipelineManager DONE ====" << std::endl;
}




DataManager* PipelineManager::getDataManager() {
	return dataManager;
}


void PipelineManager::addCharacterPipeline(std::string characterName) {//, Pipeline* pipeline) {
	Pipeline* pipeline = new Pipeline(characterName);
	pipeline->addLayer((PipelineMiddleLayer*) new IdleGenerationLayer(dataManager, characterName));
	pipeline->addLayer((PipelineMiddleLayer*) new AnimationGenerationLayer(dataManager, characterName));
	pipeline->addLayer((PipelineMiddleLayer*) new AnimationCutterLayer(dataManager, characterName));
	pipeline->createInnerQueues();
	
	PackageQueue* queue = new PackageQueue(networkLayer, NULL);
	networkLayer->setOutputQueue(characterName, queue);
	pipeline->setInputQueue(queue);
	
	queue = renderingLayer->getInputQueue();
	if (queue == NULL) {
		queue = new PackageQueue(NULL, renderingLayer);
		renderingLayer->setInputQueue(queue);
	}
	pipeline->setOutputQueue(queue);
	
	pipelineMap[characterName] = pipeline;
	
	pipeline->run();
}


Pipeline* PipelineManager::getCharacterPipeline(std::string characterName) {
	Pipeline* pipeline = NULL;
	if (pipelineMap.find(characterName) != pipelineMap.end()) {
		pipeline = pipelineMap[characterName];
	}
	return pipeline;
}

void PipelineManager::removeCharacterPipeline(std::string characterName) {
	PipelineMap::iterator it = pipelineMap.find(characterName);
	if (it != pipelineMap.end()) {
		//delete it->second;
		//pipelineMap.erase(it);
		removeCharacterPipeline(it);
	}
}

void PipelineManager::removeCharacterPipeline(PipelineMap::iterator it) {
	std::string characterName = it->first;
	std::cout << "------REMOVING PIPELINE OF CHARACTER " << characterName << "   BEGIN" <<  std::endl;
	delete it->second;
	std::cout << "------REMOVING PIPELINE OF CHARACTER " << characterName << "   MIDDLE" <<  std::endl;
	pipelineMap.erase(it);
	std::cout << "------REMOVING PIPELINE OF CHARACTER " << characterName << "   END" << std::endl;
}


void PipelineManager::removeAllCharacterPipelines() {
	while (pipelineMap.size() > 0) {
		removeCharacterPipeline(pipelineMap.begin());
	}
}

} // end of namespace
