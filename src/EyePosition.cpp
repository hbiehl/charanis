/*
 *  EyePosition.cpp
 *  Charanis
 *
 *  Created by Holger Biehl on 20.11.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "EyePosition.h"

namespace Charanis {


EyePosition::EyePosition(Ogre::Real time, Ogre::Real leftRight, Ogre::Real upDown) :
time(time), leftRight(leftRight), upDown(upDown) {};
		
Ogre::Real EyePosition::getTime() {
	return time;
}

void EyePosition::setTime(Ogre::Real time) {
	this->time = time;
}
		
Ogre::Real EyePosition::getLeftRight() {
	return leftRight;
}

void EyePosition::setLeftRight(Ogre::Real leftRight) {
	this->leftRight = leftRight;
}
		
Ogre::Real EyePosition::getUpDown() {
	return upDown;
}

void EyePosition::setUpdDown(Ogre::Real upDown) {
	this->upDown = upDown;
}

} // end of namespace