/*
 *  PipelineMiddleLayer.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 23.04.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef PIPELINE_MIDDLE_LAYER_H
#define PIPELINE_MIDDLE_LAYER_H

#include "SDL/SDL.h"
#include "PipelineLayer.h"


namespace Charanis {

class PipelineMiddleLayer : public PipelineLayer {
	private:
		std::string characterName;
		
		boost::mutex thread_mutex;
		boost::condition threadFinished_condition;
		
	protected:
		boost::thread* thread;
		
		virtual void handlePackage(Package* package);
		virtual void noPackageReceived();
		
	public:
		PipelineMiddleLayer(DataManager* dm, std::string characterName, std::string layerName);
		~PipelineMiddleLayer();
	
		virtual void run();
		virtual void __run__();
		
		std::string getCharacterName();
};

} // end of namespace

#endif