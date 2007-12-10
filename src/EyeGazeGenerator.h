/*
 *  EyeGazeGenerator.h
 *  Charanis
 *
 *  Created by Holger Biehl on 10.12.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef EYE_GAZE_GENERATOR
#define EYE_GAZE_GENERATOR

#include "Generator.h"

namespace Charanis {

/**
 * \brief %Generator zur Erzeugung einer automatischen Augenbewegung
 *
 * Dieser Generator erzeugt eine automatische Grundbewegung der Augen.
 */

class EyeGazeGenerator : public Generator {
	private:
		std::string leyeBoneName;
		std::string reyeBoneName;
		Ogre::Quaternion* lastQuaternion;
		
	public:
		EyeGazeGenerator(DataManager* dataManager, std::string characterName);
		~EyeGazeGenerator();
		
		void execute(CharacterDataPackage* pkg);
};

} // end of namespace

#endif