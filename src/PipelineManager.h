/*
 *  PipelineManager.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 01.04.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef PIPELINE_MANAGER_H
#define PIPELINE_MANAGER_H

// std includes
#include <string>
// project includes
#include "PipelineMap.h"


namespace Charanis {

class DataManager;
class NetworkLayer;
class RenderingLayer;
class Pipeline;

/**
 * \brief Verwaltung mehrerer Pipeline s.
 *
 * Über diese Klasse können mehrere Pipelines verwaltet werden. Der EngineManager nutzt dies zur Verwaltung der Charakter-Pipelines.
 */
class PipelineManager {
	private:
	
		DataManager* dataManager;
		PipelineMap pipelineMap;
		
		NetworkLayer* networkLayer;
		RenderingLayer* renderingLayer;
		
	public:
		PipelineManager(DataManager* dm, NetworkLayer* nl, RenderingLayer* rl);
		~PipelineManager();
		
		
		DataManager* getDataManager();
		
		void addCharacterPipeline(std::string characterName);//, Pipeline* pipeline);
		Pipeline* getCharacterPipeline(std::string characterName);
		void removeCharacterPipeline(std::string characterName);
		void removeCharacterPipeline(PipelineMap::iterator it);
		
		void removeAllCharacterPipelines();
};

} // end of namespace

#endif
