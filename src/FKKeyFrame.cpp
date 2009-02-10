/*
 *  FKKeyFrame.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 26.07.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#include "FKKeyFrame.h"
// dependency includes
#ifdef OSX
    #include <Ogre/OgreQuaternion.h>
#else
    #include <OgreQuaternion.h>
#endif

namespace Charanis {

FKKeyFrame::FKKeyFrame(Ogre::Real time) :
time(time) {
	//std::cout << "CONSTRUCTOR FK_PERFORMANCE - BEGIN" << std::endl;
	rotation = new Ogre::Quaternion();
	//std::cout << "CONSTRUCTOR FK_PERFORMANCE - DONE" << std::endl;
}


FKKeyFrame::FKKeyFrame(Ogre::Real time, Ogre::Quaternion* rotation) :
time(time) {
	//std::cout << "CONSTRUCTOR FK_PERFORMANCE - BEGIN" << std::endl;
	this->rotation = rotation;
	//std::cout << "CONSTRUCTOR FK_PERFORMANCE - BEGIN" << std::endl;
}


Ogre::Real FKKeyFrame::getTime() {
	return time;
}



Ogre::Quaternion* FKKeyFrame::getRotation() {
	return rotation;
}



void FKKeyFrame::setRotation(Ogre::Quaternion* rotation) {
	this->rotation=rotation;
}

} // end of namespace
