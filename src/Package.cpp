/*
 *  Package.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 17.08.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "Package.h"

namespace Charanis {

Package::Package(PackageType type) {//, unsigned long id) {
	this->type = type;
	//this->id = id;
}

Package::~Package() {
}



		
Package::PackageType Package::getType() {
	return type;
}


/*
unsigned long Package::getId() {
	return id;
}
*/

} // end of namespace
