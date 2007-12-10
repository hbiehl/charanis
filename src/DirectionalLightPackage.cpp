/*
 *  DirectionalLightPackage.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 25.08.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "DirectionalLightPackage.h"

namespace Charanis {

DirectionalLightPackage::DirectionalLightPackage(std::string lightName, Ogre::ColourValue* diffuseColour, Ogre::ColourValue* specularColour, Ogre::Vector3* direction)
: Package::Package(DIRECTIONAL_LIGHT_PACKAGE_TYPE) {
	this->lightName = lightName;
	this->direction = direction;
	this->diffuseColour = diffuseColour;
	this->specularColour = specularColour;
}


DirectionalLightPackage::~DirectionalLightPackage() {
	delete direction;
	delete diffuseColour;
	delete specularColour;
}

		
std::string DirectionalLightPackage::getLightName() {
	return lightName;
}


Ogre::ColourValue* DirectionalLightPackage::getDiffuseColour() {
	return diffuseColour;
}


Ogre::ColourValue* DirectionalLightPackage::getSpecularColour() {
	return specularColour;
}

Ogre::Vector3* DirectionalLightPackage::getDirection() {
	return direction;
}

} // end of namespace