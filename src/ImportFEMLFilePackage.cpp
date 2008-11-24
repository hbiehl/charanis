/*
 *  ImportFEMLFilePackage.cpp
 *  Charanis
 *
 *  Created by Holger Biehl on 10.12.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#include "ImportFEMLFilePackage.h"

namespace Charanis {

ImportFEMLFilePackage::ImportFEMLFilePackage(std::string characterName, std::string fileName) :
Package(IMPORT_FEML_FILE_PACKAGE_TYPE) {
	this->characterName = characterName;
	this->fileName = fileName;
}
		
std::string ImportFEMLFilePackage::getCharacterName() {
	return characterName;
}

std::string ImportFEMLFilePackage::getFileName() {
	return fileName;
}

} // end of namespace