/*
 *  AddObjectPackage.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 06.09.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef ADD_OBJECT_PACKAGE_H
#define ADD_OBJECT_PACKAGE_H

#include <string>
#include <vector>

#include "SDL/SDL.h"
#include "Ogre/Ogre.h"
#include "Package.h"

namespace Charanis {


/**
 * \bief Paket zum Hinzufügen von Objekten in die Szene.
 *
 * Mit diesem Paket wird dem RenderingLayer mitgeteilt, ein neues Objekt einzulesen und in der Szene zu platzieren.
 */
class AddObjectPackage : public Package {
	private:
		std::string objectName;
		std::string meshName;
		Ogre::Vector3* position;
		Ogre::Quaternion* orientation;
		Ogre::Real scale;
		
		
	public:
		AddObjectPackage(std::string objectName, std::string meshName, Ogre::Vector3* position, Ogre::Quaternion* orientation, Ogre::Real scale=1);
		~AddObjectPackage();
		
		
		std::string getObjectName();
		std::string getMeshName();
		Ogre::Vector3* getPosition();
		Ogre::Quaternion* getOrientation();
		Ogre::Real getScale();
};

} // end of namespace

#endif