/*
 *  RemoveCharacterPackage.h
 *  Charanis
 *
 *  Created by Holger Biehl on 09.12.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef REMOVE_CHARACTER_PACKAGE_H
#define REMOVE_CHARACTER_PACKAGE_H

#include <string>

#include "Package.h"

namespace Charanis {


/**
 * \brief Paket zum Entfernen eines Charakters aus der Szene.
 *
 * Dieses Paket teilt dem RenderingLayer mit, das Character -Objekt des spezifizierten Charakers aus der Szene zu entfernen und zu löschen.
 */
class RemoveCharacterPackage : public Package {
	private:
		std::string characterName;
	
	public:
		RemoveCharacterPackage(std::string name);
		
		std::string getCharacterName();
};

}

#endif