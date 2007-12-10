/*
 *  CharacterSoundPackage.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 07.09.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef CHARACTER_SOUND_PACKAGE
#define CHARACTER_SOUND_PACKAGE


#include <string>

#include "SDL/SDL.h"
#include "Ogre/Ogre.h"

#include "Package.h"

namespace Charanis {

/**
 * \brief Paket zum Abspielen einer Audio-Datei.
 *
 * Dieses Paket transportiert einen Abspiel-Befehl einer Audio-Datei.
 */
class CharacterSoundPackage : public Package {
	private:
		std::string characterName;
		std::string fileName;
		Ogre::Real startTime;
		
		
	public: 
		CharacterSoundPackage(std::string characterName, std::string fileName, Ogre::Real startTime);
		~CharacterSoundPackage();

		std::string getCharacterName();
		std::string getFileName();
		Ogre::Real getStartTime();
};

} // end of namespace

#endif