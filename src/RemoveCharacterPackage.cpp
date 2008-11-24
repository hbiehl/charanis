/*
 *  RemoveCharacterPackage.cpp
 *  Charanis
 *
 *  Created by Holger Biehl on 09.12.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#include "RemoveCharacterPackage.h"

namespace Charanis {

RemoveCharacterPackage::RemoveCharacterPackage(std::string name) :
Package(REMOVE_CHARACTER_PACKAGE_TYPE), characterName(name) {
	// Nothing to do
}
		
std::string RemoveCharacterPackage::getCharacterName() {
	return characterName;
}

} // end of namespace