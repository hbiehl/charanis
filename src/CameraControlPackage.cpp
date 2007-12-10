/*
 *  CameraControlPackage.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 06.09.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "CameraControlPackage.h"

namespace Charanis {

CameraControlPackage::CameraControlPackage(Ogre::Vector3* position, Ogre::Vector3* direction) :
Package(Package::CAMERA_CONTROL_PACKAGE_TYPE) {
	this->position = position;
	this->direction = direction;
}



CameraControlPackage::~CameraControlPackage() {}


		
Ogre::Vector3* CameraControlPackage::getPosition() {
	return position;
}



Ogre::Vector3* CameraControlPackage::getDirection() {
	return direction;
}

} // end of namespace