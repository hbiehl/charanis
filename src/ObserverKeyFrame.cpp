/*
 *  ObserverKeyFrame.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 02.10.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "ObserverKeyFrame.h"

namespace Charanis {

ObserverKeyFrame::ObserverKeyFrame(Ogre::Real time, Ogre::Vector3 position, Ogre::Vector3 direction) {//, Ogre::Vector3 up, Ogre::Quaternion orientation) {
	this->time = time;
	this->position = position;
	//this->up = up;
	this->direction = direction;
	//this->orientation = orientation;
}

ObserverKeyFrame::~ObserverKeyFrame() {}
		
Ogre::Real ObserverKeyFrame::getTime() {
	return this->time;
}

void ObserverKeyFrame::setTime(Ogre::Real time) {
	this->time = time;
}
		
Ogre::Vector3 ObserverKeyFrame::getPosition() {
	return this->position;
}

void ObserverKeyFrame::setPosition(Ogre::Vector3 position) {
	this->position = position;
}
		

/*
Ogre::Quaternion ObserverKeyFrame::getOrientation() {
	return this->orientation;
}

void ObserverKeyFrame::setOrientation(Ogre::Quaternion orientation) {
	this->orientation = orientation;
}
*/

Ogre::Vector3 ObserverKeyFrame::getDirection() {
	return direction;
}

void ObserverKeyFrame::setDirection(Ogre::Vector3 direction) {
	this->direction = direction;
}
/*
Ogre::Vector3 ObserverKeyFrame::getUp() {
	return up;
}

void ObserverKeyFrame::setUp(Ogre::Vector3 up) {
	this->up = up;
}





Ogre::Radian ObserverKeyFrame::getRoll() {
	return roll;
}

void ObserverKeyFrame::setRoll(Ogre::Radian roll) {
	this->roll = roll;
}

		
Ogre::Radian ObserverKeyFrame::getPitch() {
	return pitch;
}

void ObserverKeyFrame::setPitch(Ogre::Radian pitch) {
	this->pitch = pitch;
}

		
Ogre::Radian ObserverKeyFrame::getYaw() {
	return yaw;
}

void ObserverKeyFrame::setYaw(Ogre::Radian yaw) {
	this->yaw = yaw;
}
*/

} // end of namespace
