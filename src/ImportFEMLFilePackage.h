/*
 *  ImportFEMLFilePackage.h
 *  Charanis
 *
 *  Created by Holger Biehl on 10.12.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef IMPORT_FEML_FILE_PACKAGE_H
#define IMPORT_FEML_FILE_PACKAGE_H

#include <string>

#include "Package.h"

namespace Charanis {

class ImportFEMLFilePackage : public Package {
	private:
		std::string characterName;
		std::string fileName;
		
		
	public:
		ImportFEMLFilePackage(std::string characterName, std::string fileName);
		
		std::string getCharacterName();
		std::string getFileName();
};

} // end of namespace

#endif