/*
 *  AddCharacterPackage.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 24.08.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "AddCharacterPackage.h"

namespace Charanis {

AddCharacterPackage::AddCharacterPackage(std::string characterName, std::string meshName, Ogre::Vector3* position, Ogre::Vector3* direction, Ogre::Real scale)
: Package(ADD_CHARACTER_PACKAGE_TYPE) {
	std::cout << "AddCharacterPackage BEGIN" << std::endl;
	this->characterName = characterName;
	this->meshName = meshName;
	this->position = position;
	this->direction = direction;
	this->scale = scale;
	
	femlFiles = new std::vector<std::string>();
	std::cout << "AddCharacterPackage END" << std::endl;
}


AddCharacterPackage::~AddCharacterPackage() {
	delete femlFiles;
}
		
void AddCharacterPackage::addFEMLFile(std::string femlFile) {
	femlFiles->push_back(femlFile);
}
		
std::vector<std::string>* AddCharacterPackage::getFEMLFiles() {
	return femlFiles;
}
		
std::string AddCharacterPackage::getCharacterName() {
	return characterName;
}

std::string AddCharacterPackage::getMeshName() {
	return meshName;
}

Ogre::Vector3* AddCharacterPackage::getPosition() {
	return position;
}

Ogre::Vector3* AddCharacterPackage::getDirection() {
	return direction;
}

Ogre::Real AddCharacterPackage::getScale() {
	return scale;
}

} // end of namespace