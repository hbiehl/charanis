/*
 *  Pipeline.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 09.08.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef PIPELINE_H
#define PIPELINE_H

#include <vector>


#include "CharacterDataPackage.h"
#include "PipelineMiddleLayer.h"
#include "PackageQueue.h"

namespace Charanis {


/** 
 * \brief Verwaltung einer Pipeline.
 *
 * Diese Klasse dient zur Repräsentation und Verwaltung einer %Pipeline. Eine %Pipeline besteht aus mehreren PipelineMiddleLayer s, die über PackageQueue s
 * miteinander verbunden sind. Momentan gibt es in dem System nur Charakter-Pipelines.
 */
class Pipeline {
	private:
		std::vector<PipelineMiddleLayer*> pipelineLayerVec;
		
		std::string characterName;
	
	public:
		Pipeline(std::string characterName);
		~Pipeline();
		
		void addLayer(PipelineMiddleLayer* layer);
		void Pipeline::addLayer(int position, PipelineMiddleLayer* layer);
		void removeLayer(int position);
		
		void createInnerQueues();

		void setInputQueue(PackageQueue* queue);
		void setOutputQueue(PackageQueue* queue);
		
		void run();
};

} // end of namespace

#endif