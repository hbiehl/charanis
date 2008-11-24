/*
 *  Generator.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 10.11.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "Generator.h"
// std includes
#include <iostream>
#include <sstream>

namespace Charanis {

Generator::Generator(DataManager* dataManager, std::string characterName, std::string generatorName) :
characterName(characterName), generatorName(generatorName) {
	this->dataManager = dataManager;
	animationNo=1;
}


Generator::~Generator() {}


std::string Generator::generateAnimationName() {
	if (animationNo == ULONG_MAX) {
		animationNo = 1; 
	}
	
	std::stringstream animationNameStream;
	animationNameStream << generatorName << "_" << characterName << "_" << animationNo++;	
	std::string animationName;
	animationNameStream >> animationName;
	return animationName;
}


DataManager* Generator::getDataManager() {
	return dataManager;
}


std::string Generator::getCharacterName() {
	return characterName;
}


std::string Generator::getGeneratorName() {
	return generatorName;
}


void Generator::execute(CharacterDataPackage* pkg) {
	std::cout << generatorName << ".execute(CharacterDataPackage* pkg)    ---  NOT IMPLEMENTED YET" << std::endl;
}

} // end of namespace