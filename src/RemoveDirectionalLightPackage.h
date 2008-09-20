/*
 *  RemoveDirectionalLightPackage.h
 *  Charanis
 *
 *  Created by Holger Biehl on 09.12.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef REMOVE_DIRECTIONAL_LIGHT_PACKAGE_H
#define REMOVE_DIRECTIONAL_LIGHT_PACKAGE_H

// std includes
#include <string>
// project includes
#include "Package.h"

namespace Charanis {

/**
 * \brief Paket zum Entfernen einer gerichteten Lichtquelle aus der Szene.
 *
 * Dieses Paket teilt dem RenderingLayer mit, die spezifizierte gerichtete Lichtquelle aus der Szene zu entfernen und zu löschen.
 */
class RemoveDirectionalLightPackage : public Package {
	private:
		std::string lightName;
	
	public:
		RemoveDirectionalLightPackage(std::string name);
		
		std::string getLightName();
};

} // end of namespace

#endif
