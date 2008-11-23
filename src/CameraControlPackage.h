/*
 *  CameraControlPackage.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 06.09.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef CAMERA_CONTROL_PACKAGE_H
#define CAMERA_CONTROL_PACKAGE_H


#include "Ogre/Ogre.h"
#include "Package.h"

namespace Charanis {

/**
 * \brief Paket zur Steuerung der Kamera.
 *
 * Mit diesem Paket werden dem RenderingLayer Informationen zur Bewegung des Observer übertragen.
 * Aktuell ist dies nur eine neue Kameraposition und -richtung. Künftig soll der Observer
 * aber auch über keyframes gesteuert werden können - womit dann kontrollierte Kamerafahrten 
 * möglich wären. Das Observer-Objekt ist auf die keyframebasierte Bewegung sogar schon 
 * vorbereitet.
 */
class CameraControlPackage : public Package {
	private:
		Ogre::Vector3* position;
		Ogre::Vector3* direction;
		
	public:
		CameraControlPackage(Ogre::Vector3* position, Ogre::Vector3* direction);
		~CameraControlPackage();
		
		Ogre::Vector3* getPosition();
		Ogre::Vector3* getDirection();
};

} // end of namespace

#endif