/*
 *  ImportSAMLFilePackage.h
 *  Charanis
 *
 *  Created by Holger Biehl on 10.12.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IMPORT_SAML_FILE_PACKAGE_H
#define IMPORT_SAML_FILE_PACKAGE_H

// std includes
#include <string>
// project includes
#include "Package.h"


namespace Charanis {

class ImportSAMLFilePackage : public Package {
	private:
		std::string characterName;
		std::string fileName;
		
		
	public:
		ImportSAMLFilePackage(std::string characterName, std::string fileName);
		
		std::string getCharacterName();
		std::string getFileName();
};

} // end of namespace

#endif
