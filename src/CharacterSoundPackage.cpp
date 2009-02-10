/*
 *  CharacterSoundPackage.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 07.09.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "CharacterSoundPackage.h"

namespace Charanis {


CharacterSoundPackage::CharacterSoundPackage(std::string characterName, std::string fileName, Ogre::Real startTime) 
: Package(CHARACTER_SOUND_PACKAGE_TYPE), characterName(characterName), fileName(fileName), startTime(startTime) {
}



CharacterSoundPackage::~CharacterSoundPackage() {
}


std::string CharacterSoundPackage::getCharacterName() {
	return characterName;
}


std::string CharacterSoundPackage::getFileName() {
	return fileName;
}


Ogre::Real CharacterSoundPackage::getStartTime() {
	return startTime;
}

} // end of namespace
