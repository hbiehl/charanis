/*
 *  RemoveObjectPackage.cpp
 *  Charanis
 *
 *  Created by Holger Biehl on 09.12.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#include "RemoveObjectPackage.h"

namespace Charanis {

RemoveObjectPackage::RemoveObjectPackage(std::string name) :
Package(REMOVE_OBJECT_PACKAGE_TYPE), objectName(name) {}

		
std::string RemoveObjectPackage::getObjectName() {
	return objectName;
}

} // end of namespace
