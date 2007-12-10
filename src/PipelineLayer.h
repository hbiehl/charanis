/*
 *  PipelineLayer.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 01.04.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef PIPELINE_LAYER_H
#define PIPELINE_LAYER_H

#include "SDL/SDL.h"

#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <string>

#include "PackageQueue.h"
#include "DataManager.h"

//boost::mutex io_mutex;

namespace Charanis {

/**
 * \brief Eine Stufe einer Pipeline.
 *
 * Jede Pipelinestufe läuft in einem eigenen Thread.
 */
class PipelineLayer {
	private:
		std::string name;

		
		PackageQueue* inputQueue;
		PackageQueue* outputQueue;
		
	protected:
		DataManager* dataManager;
		
	public:
		PipelineLayer(DataManager* dm, std::string name);
		~PipelineLayer();
		
				
		std::string getName();
		
		PackageQueue* getInputQueue();
		PackageQueue* getOutputQueue();
		
		void setInputQueue(PackageQueue* queue);
		void setOutputQueue(PackageQueue* queue);

		DataManager* getDataManager();

		
		virtual void run();		
};


} // end of namespace

#endif