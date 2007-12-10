/*
 *  AnimationCutterLayer.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 18.06.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef ANIMATION_CUTTER_LAYER_H
#define ANIMATION_CUTTER_LAYER_H


#include "PipelineMiddleLayer.h"
#include "CharacterDataPackage.h"


namespace Charanis {

class AnimationCutterLayer : PipelineMiddleLayer {
	private:
		CharacterPerformanceVector performanceVector;
		
	protected:
		void handlePackage(Package* package);
	
	public:
		AnimationCutterLayer(DataManager* dm, std::string characterName);
};

} // end of namespace

#endif