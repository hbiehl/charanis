/*
 *  EyeGazeGenerator.cpp
 *  Charanis
 *
 *  Created by Holger Biehl on 10.12.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "EyeGazeGenerator.h"

namespace Charanis {

EyeGazeGenerator::EyeGazeGenerator(DataManager* dataManager, std::string characterName) :
Generator(dataManager, characterName, "EyeGazeGenerator") {
	//boneName = "Joint10";
	leyeBoneName = "l_eyeball_joint";
	reyeBoneName = "r_eyeball_joint";
	
	lastQuaternion = new Ogre::Quaternion(1, 0, 0, 0);
}


EyeGazeGenerator::~EyeGazeGenerator() {
	std::cout << "EyeGazeGenerator::~EyeGazeGenerator()" << std::endl;
	delete lastQuaternion;
} 

void EyeGazeGenerator::execute(CharacterDataPackage* pkg) {
	std::cout << getGeneratorName() << ".execute() +++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
	std::string animationName = generateAnimationName();
	std::cout << "generating animation " << animationName << "   " << pkg->getStartTime() << "-" << pkg->getEndTime() <<  std::endl;
	
	
	FKPerformance* fkPerformance = new FKPerformance(animationName, getCharacterName(), pkg->getLength());
	

	
	FKTrack* leftEyeTrack = new FKTrack(leyeBoneName);
	FKTrack* rightEyeTrack = new FKTrack(reyeBoneName);
	leftEyeTrack->addKeyFrame(new FKKeyFrame(0, lastQuaternion));
	rightEyeTrack->addKeyFrame(new FKKeyFrame(0, lastQuaternion));
	std::cout << "ADDING KEY FRAME " << getCharacterName() << "   --   " << 0 << " " << *lastQuaternion << std::endl;
	
	
	
	Ogre::Real pkgLength = pkg->getLength();

	Ogre::Real currentTime = 0;
	while (pkgLength - currentTime > 2) {
		currentTime += 0.5 + getDataManager()->randomAlpha(); // 0.5 bis 1.5 Sekunden weiter
		
		//Ogre::Quaternion* q = new Ogre::Quaternion(0.8+0.2*getDataManager()->randomAlpha(), 0.5-getDataManager()->randomAlpha(), 0.5-getDataManager()->randomAlpha(), 0.5-getDataManager()->randomAlpha());
		
		Ogre::Quaternion* q = new Ogre::Quaternion(Ogre::Degree(60*getDataManager()->randomAlpha()), Ogre::Vector3(0.5-getDataManager()->randomAlpha(), 0.5-getDataManager()->randomAlpha(), 0.5-getDataManager()->randomAlpha()));
		leftEyeTrack->addKeyFrame(new FKKeyFrame(currentTime, q));
		rightEyeTrack->addKeyFrame(new FKKeyFrame(currentTime, q));
		std::cout << "ADDING KEY FRAME " << getCharacterName() << "   --   " << currentTime << " " << *q << std::endl;
	}

	//Ogre::Real randomTime = (0.25 + 0.5*getDataManager()->randomAlpha() ) * pkgLength;
	Ogre::Real randomTime = currentTime + 0.5 + getDataManager()->randomAlpha();
	Ogre::Quaternion* q = new Ogre::Quaternion(Ogre::Degree(60*getDataManager()->randomAlpha()), Ogre::Vector3(0.5-getDataManager()->randomAlpha(), 0.5-getDataManager()->randomAlpha(), 0.5-getDataManager()->randomAlpha()));
	leftEyeTrack->addKeyFrame(new FKKeyFrame(randomTime, q));
	rightEyeTrack->addKeyFrame(new FKKeyFrame(randomTime, q));
	std::cout << "ADDING KEY FRAME " << getCharacterName() << "   --   " << randomTime << " " << *q << std::endl;
	
	
	lastQuaternion = new Ogre::Quaternion(Ogre::Degree(60*getDataManager()->randomAlpha()), Ogre::Vector3(0.5-getDataManager()->randomAlpha(), 0.5-getDataManager()->randomAlpha(), 0.5-getDataManager()->randomAlpha()));
	leftEyeTrack->addKeyFrame(new FKKeyFrame(pkgLength, new Ogre::Quaternion(*lastQuaternion)));
	rightEyeTrack->addKeyFrame(new FKKeyFrame(pkgLength, new Ogre::Quaternion(*lastQuaternion)));
	fkPerformance->addTrack(leftEyeTrack);
	fkPerformance->addTrack(rightEyeTrack);
	std::cout << "ADDING KEY FRAME " << getCharacterName() << "   --   " << pkgLength << " " << *lastQuaternion << std::endl;
	
	
	CharacterPerformance* cp = new CharacterPerformance(getCharacterName(), animationName, pkg->getStartTime(), 0, 0, pkg->getEndTime(), 0);
	cp->setManualPerformance(true);
	fkPerformance->setCharacterPerformance(cp);
	

	pkg->addFKPerformance(fkPerformance);
	
}

} // end of namespace