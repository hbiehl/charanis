/*
 *  ImportSAMLFilePackage.cpp
 *  Charanis
 *
 *  Created by Holger Biehl on 10.12.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#include "ImportSAMLFilePackage.h"


namespace Charanis {

ImportSAMLFilePackage::ImportSAMLFilePackage(std::string characterName, std::string fileName) :
Package(IMPORT_SAML_FILE_PACKAGE_TYPE) {
	this->characterName = characterName;
	this->fileName = fileName;
}


std::string ImportSAMLFilePackage::getCharacterName() {
	return characterName;
}
		

std::string ImportSAMLFilePackage::getFileName() {
	return fileName;
}

} // end of namespace