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


#include <Ogre/Ogre.h>

#include <vector>

#include <boost/random.hpp>
#include <boost/random/linear_congruential.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>


#include "PipelineMiddleLayer.h"
#include "CharacterDataPackage.h"

#include "Generator.h"
#include "EyeGazeGenerator.h"
#include "HeadMovementGenerator.h"

namespace Charanis {

class AnimationGenerationLayer : PipelineMiddleLayer {
	private:
		//Ogre::Real time;
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