/*
 *  RemoveDirectionalLightPackage.cpp
 *  Charanis
 *
 *  Created by Holger Biehl on 09.12.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "RemoveDirectionalLightPackage.h"

namespace Charanis {

RemoveDirectionalLightPackage::RemoveDirectionalLightPackage(std::string name) :
Package(REMOVE_DIRECTIONAL_LIGHT_PACKAGE_TYPE), lightName(name) {}
		
std::string RemoveDirectionalLightPackage::getLightName() {
	return lightName;
}

} // end of namespace