/*
 *  AnimationGenerationLayer.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 03.11.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef ANIMATION_GENERATION_LAYER_H
#define ANIMATION_GENERATION_LAYER_H

// std includes
#include <vector>
// project includes
#include "PipelineMiddleLayer.h"

namespace Charanis {

class DataManager;
class Generator;

class AnimationGenerationLayer : PipelineMiddleLayer {
	private:
		unsigned long animationNo;
		std::vector<Generator*> generatorVector;
		
		
	protected:
		void handlePackage(Package* package);
		//void noPackageReceived();
	
	public:
		AnimationGenerationLayer(DataManager* dm, std::string characterName);
		~AnimationGenerationLayer();
};

} // end of namespace

#endif