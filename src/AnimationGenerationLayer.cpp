/*
 *  AnimationGenerationLayer.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 03.11.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "AnimationGenerationLayer.h"


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
	
	/*
	std::string animationName;
	std::stringstream animationNameStream;
	animationNameStream << "GENERATOR_TEST_" << getCharacterName() << "_" << animationNo++;
	animationNameStream >> animationName;
	FKPerformance* fkPerformance = new FKPerformance(animationName, getCharacterName(), pkg->getLength());
	
	
	Ogre::Real randomNoise = (float) dataManager->random100() / 100.0; // randomNoise in [0;1]
	std::cout << "RAMDOM_NOISE=" << randomNoise << std::endl;
	
	FKTrack* fkTrack = new FKTrack("Joint14");
	fkTrack->addKeyFrame(new FKKeyFrame(FKKeyFrame(0, new Ogre::Quaternion(1, 0, 0, 0))));
	fkTrack->addKeyFrame(new FKKeyFrame(FKKeyFrame((0.25+0.5*randomNoise ) * pkg->getLength(), new Ogre::Quaternion(0.5+randomNoise, 0, randomNoise, 1))));
	fkTrack->addKeyFrame(new FKKeyFrame(FKKeyFrame(pkg->getLength(), new Ogre::Quaternion(1, 0, 0, 0))));
	fkPerformance->addTrack(fkTrack);
	
	
	CharacterPerformance* cp = new CharacterPerformance(getCharacterName(), animationName, pkg->getStartTime(), 0, 0, pkg->getEndTime(), 0);
	cp->setManualPerformance(true);
	fkPerformance->setCharacterPerformance(cp);
	//new CharacterPerformance(getCharacterName(), "Idle", time, time+IDLE_TIME)
	pkg->addFKPerformance(fkPerformance);
	*/
	std::cout << "===================== ANIMATION_GENERATION_LAYER.handlePackage() /" << getCharacterName() <<"/ END" << std::endl;
}

} // end of namespace