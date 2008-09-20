/*
 *  AddObjectPackage.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 06.09.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#include "AddObjectPackage.h"
// dependency includes
#ifdef OSX
    #include <Ogre/OgreQuaternion.h>
    #include <Ogre/OgreVector3.h>
#else
    #include <OgreQuaternion.h>
    #include <OgreVector3.h>
#endif

namespace Charanis {

AddObjectPackage::AddObjectPackage(std::string objectName, std::string meshName, Ogre::Vector3* position, Ogre::Quaternion* orientation, Ogre::Real scale)
: Package(ADD_OBJECT_PACKAGE_TYPE) {
	std::cout << "AddObjectPackage BEGIN" << std::endl;
	this->objectName = objectName;
	this->meshName = meshName;
	this->position = position;
	this->orientation = orientation;
	this->scale = scale;
	
	std::cout << "AddObjectPackage END" << std::endl;
}


AddObjectPackage::~AddObjectPackage() {
}
		

		
std::string AddObjectPackage::getObjectName() {
	return objectName;
}

std::string AddObjectPackage::getMeshName() {
	return meshName;
}

Ogre::Vector3* AddObjectPackage::getPosition() {
	return position;
}

Ogre::Quaternion* AddObjectPackage::getOrientation() {
	return orientation;
}

Ogre::Real AddObjectPackage::getScale() {
	return scale;
}

} // end of namespace
