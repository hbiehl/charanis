/*
 *  CameraControlPackage.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 06.09.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#include "CameraControlPackage.h"
// dependency includes
#ifdef OSX
    #include <Ogre/OgreVector3.h>
#else
    #include <OgreVector3.h>
#endif

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
