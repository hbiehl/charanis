/*
 *  AnimationCutterLayer.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 18.06.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#include "AnimationCutterLayer.h"

// project includes
#include "CharacterDataPackage.h"

namespace Charanis {


AnimationCutterLayer::AnimationCutterLayer(DataManager* dm, std::string characterName) 
: PipelineMiddleLayer(dm, characterName, "AnimationCutterLayer") {}


void AnimationCutterLayer::handlePackage(Package* package) {
	CharacterDataPackage* chPackage = (CharacterDataPackage*) package;
	//std::cout << std::endl << "MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM - ANIMATION_CUTTER_LAYER: handleDataPackage(...) - "<< chPackage->getStartTime() << " - MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM" << std::endl << std::endl;
	// add all Performances of the performanceVector
	for (int i=0; i<performanceVector.size(); i++) {
		std::cout << "[AnimationCutterLayer] +++++++++++ adding CharacterPerformance ++++++++++" << std::endl;
		chPackage->addCharacterPerformance(performanceVector[i]);
	}
	performanceVector.clear();
	
	
	
	
	
	Ogre::Real packageEndTime = chPackage->getEndTime();
	

	std::string characterName = chPackage->getCharacterName();
	CharacterPerformanceVector* cpv = chPackage->getAllCharacterPerformances();
	
	for (CharacterPerformanceVector::iterator performanceIt=cpv->begin(); performanceIt!=cpv->end();) {
		CharacterPerformance* performance = *performanceIt;
		
		if (performance->getStartTime() >= packageEndTime) {
			performanceVector.push_back(performance);
			performanceIt = cpv->erase(performanceIt);
		} else {
			if (performance->getEndTime() > packageEndTime) {
				CharacterPerformance* cutPerformance = performance->cutPerformance(packageEndTime);
				if (cutPerformance!=NULL) {
					performanceVector.push_back(cutPerformance);
				}
			}
			performanceIt++;
		}
	}
}
	
} // end of namespace
