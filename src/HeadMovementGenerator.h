/*
 *  HeadMovementGenerator.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 10.11.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef HEAD_MOVEMENT_GENERATOR
#define HEAD_MOVEMENT_GENERATOR

#include "Generator.h"

namespace Charanis {

/**
 * \brief %Generator zur Erzeugung einer automatischen Kopfbewegung
 *
 * Dieser Generator erzeugt eine automatische Grundbewegung des Kopfes.
 */

class HeadMovementGenerator : public Generator {
	private:
		std::string boneName;
		Ogre::Quaternion* lastQuaternion;
		
	public:
		HeadMovementGenerator(DataManager* dataManager, std::string characterName);
		~HeadMovementGenerator();
		
		void execute(CharacterDataPackage* pkg);
};


} // end of namespace

#endif