/*
 *  BodyAnimationLibrary.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 28.05.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "BodyAnimationLibrary.h"

// std includes
#include <iostream>

// project includes
#include "BodyAnimation.h"
//#include "SAMLParser.h"

namespace Charanis {

BodyAnimationLibrary::BodyAnimationLibrary(std::string characterName) {
	this->characterName = characterName;
}



BodyAnimationLibrary::~BodyAnimationLibrary() {
	for (BodyAnimationMap::iterator it=animationMap.begin(); it!=animationMap.end(); it++) {
		delete it->second;
	}
	
	animationMap.clear();
}
	
	
	


	
	
std::string BodyAnimationLibrary::getCharacterName() {
	return characterName;
}


		
void BodyAnimationLibrary::addBodyAnimation(BodyAnimation* anim) {
	animationMap[anim->getName()] = anim;
}



BodyAnimation* BodyAnimationLibrary::getBodyAnimation(std::string animName) {
	if (animationMap.find(animName) != animationMap.end()) {
		return animationMap[animName];
	} else {
		return NULL;
	}
}



void BodyAnimationLibrary::print() {
	std::cout << "<<<<<<<<<<<<<<<<<<<<<<< " << "Body-Animations of Character "<< characterName << " >>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
	for (BodyAnimationMap::iterator it=animationMap.begin(); it!=animationMap.end(); it++) {
		std::cout << "   - " << it->first << std::endl;
	}
}

} // end of namespace
