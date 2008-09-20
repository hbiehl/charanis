/*
 *  AmbientLightPackage.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 25.08.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef AMBIENT_LIGHT_PACKAGE_H
#define AMBIENT_LIGHT_PACKAGE_H

// project includes
#include "Package.h"

namespace Ogre {
class ColourValue;
} // end of namespace Ogre

namespace Charanis {

/**
 * \brief Paket zur Modifikation der ambienten Lichtverhältnisse.
 *
 * Dieses Paket teilt dem RenderingLayer mit, die Farbe des ambienten Lichtes zu modifizieren.
 * Zur Steuerung von gerichteten Lichtquellen dient dagegen das DirectionalLightPackage.
 */
class AmbientLightPackage : public Package {
	private:
		Ogre::ColourValue* ambientColour;
	
	public:
		AmbientLightPackage(Ogre::ColourValue* ambientColour);
		~AmbientLightPackage();
		
		Ogre::ColourValue* getAmbientColour();
};

} // end of namespace

#endif
