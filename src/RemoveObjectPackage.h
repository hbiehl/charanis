/*
 *  RemoveObjectPackage.h
 *  Charanis
 *
 *  Created by Holger Biehl on 09.12.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef REMOVE_OBJECT_PACKAGE_H
#define REMOVE_OBJECT_PACKAGE_H

// std includes
#include <string>
// project includes
#include "Package.h"

namespace Charanis {

/**
 * \brief Paket zum Entfernen eines Objektes aus der Szene.
 *
 * Dieses Paket teilt dem RenderingLayer mit, das spezifizierte Objekt aus der Szene zu entfernen und zu löschen.
 */
class RemoveObjectPackage : public Package {
	private:
		std::string objectName;
	
	public:
		RemoveObjectPackage(std::string name);
		
		std::string getObjectName();
};

} // end of namespace

#endif