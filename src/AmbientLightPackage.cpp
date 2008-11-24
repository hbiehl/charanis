/*
 *  AmbientLightPackage.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 25.08.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#include "AmbientLightPackage.h"
// dependency includes
#include <Ogre/OgreColourValue.h>

namespace Charanis {

AmbientLightPackage::AmbientLightPackage(Ogre::ColourValue* ambientColour) 
: Package::Package(AMBIENT_LIGHT_PACKAGE_TYPE) {
	this->ambientColour = ambientColour;
}

AmbientLightPackage::~AmbientLightPackage() {
	delete ambientColour;
}
		
Ogre::ColourValue* AmbientLightPackage::getAmbientColour() {
	return ambientColour;
}

} // end of namespace