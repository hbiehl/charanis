/*
 *  DirectionalLightPackage.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 25.08.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef DIRECTIONAL_LIGHT_PACKAGE_H
#define DIRECTIONAL_LIGHT_PACKAGE_H

#include <string>


#include "Ogre/Ogre.h"
#include "Package.h"

namespace Charanis {

/**
 * \brief Paket zum Steuern von Gerichteten Lichtquellen.
 *
 * Dieses Paket dient dazu, dem RenderingLayer Informationen zu gerichteten Lichtquellen mitzuteilen.
 * Über dieses Paket können neue gerichtete Lichtquellen angelegt oder existierende modifiziert werden.
 * Zur Steuerung des ambienten Lichtes dient dagegen das AmbientLightPackage.
 */
class DirectionalLightPackage : public Package {
	private:
		std::string lightName;
		Ogre::ColourValue* diffuseColour;
		Ogre::ColourValue* specularColour;
		Ogre::Vector3* direction;
	
	public:
		DirectionalLightPackage(std::string lightName, Ogre::ColourValue* diffuseColour, Ogre::ColourValue* specularColour, Ogre::Vector3* direction);
		~DirectionalLightPackage();
		
		std::string getLightName();
		Ogre::ColourValue* getDiffuseColour();
		Ogre::ColourValue* getSpecularColour();
		Ogre::Vector3* getDirection();
};

} // end of namespace

#endif