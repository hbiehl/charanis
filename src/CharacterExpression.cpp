/*
 *  CharacterExpression.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 26.05.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#include "CharacterExpression.h"
// project includes
#include "FacialExpression.h"

namespace Charanis {

CharacterExpression::CharacterExpression(Ogre::Real time, FacialExpression* expression, Ogre::Real weight) {
	this->time = time;
	this->expression=expression;
	this->weight=weight;
}

CharacterExpression::~CharacterExpression() {
	// nothing to do
}

		
FacialExpression* CharacterExpression::getExpression() {
	return expression;
}

Ogre::Real CharacterExpression::getWeight() {
	return weight;
}

Ogre::Real CharacterExpression::getTime() {
	return time;
}


void CharacterExpression::fillKeyFrame(Ogre::VertexPoseKeyFrame* kf, StringIntMap* poseMapping) {
	getExpression()->fillKeyFrame(kf, poseMapping, getWeight());
}

} // end of namespace
