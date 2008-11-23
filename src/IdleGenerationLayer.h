/*
 *  IdleGenerationLayer.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 11.06.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef IDLE_GENERATION_LAYER_H
#define IDLE_GENERATION_LAYER_H


#include <Ogre/Ogre.h>

#include "PipelineMiddleLayer.h"
#include "CharacterDataPackage.h"


namespace Charanis {

class IdleGenerationLayer : PipelineMiddleLayer {
	private:
		//Ogre::Real time;
		
		
		
		
	protected:
		void handlePackage(Package* package);
		void noPackageReceived();
	
	public:
		IdleGenerationLayer(DataManager* dm, std::string characterName);

};

} // end of namespace
#endif