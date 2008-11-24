/*
 *  AnimationGenerationLayer.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 03.11.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#include "AnimationGenerationLayer.h"
// std includes
#include <iostream>
// project includes
#include "CharacterDataPackage.h"
#include "EyeGazeGenerator.h"
#include "HeadMovementGenerator.h"

namespace Charanis {
	
AnimationGenerationLayer::AnimationGenerationLayer(DataManager* dm, std::string characterName) 
: PipelineMiddleLayer(dm, characterName, "AnimationGenerationLayer") {
	std::cout << "ANIMATION_GENERATION_LAYER KONSTRUKTOR BEGIN"<< std::endl;
	animationNo = 0;
	
	generatorVector.push_back(new HeadMovementGenerator(dm, characterName));
	generatorVector.push_back(new EyeGazeGenerator(dm, characterName));
	std::cout << "ANIMATION_GENERATION_LAYER KONSTRUKTOR END"<< std::endl;
}


AnimationGenerationLayer::~AnimationGenerationLayer() {
	for (int i=0; i<generatorVector.size(); i++) {
		delete generatorVector[i];
	}
	generatorVector.clear();
}


void AnimationGenerationLayer::handlePackage(Package* package) {
	std::cout << "===================== ANIMATION_GENERATION_LAYER.handlePackage() /" << getCharacterName() << "/ BEGIN" << std::endl;
	
	CharacterDataPackage* pkg = (CharacterDataPackage*) package;
	
	for (int i=0; i<generatorVector.size(); i++) {
		generatorVector[i]->execute(pkg);
	}
	

	std::cout << "===================== ANIMATION_GENERATION_LAYER.handlePackage() /" << getCharacterName() <<"/ END" << std::endl;
}

} // end of namespace