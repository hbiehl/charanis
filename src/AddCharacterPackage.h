/*
 *  AddCharacterPackage.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 24.08.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef ADD_CHARACTER_PACKAGE_H
#define ADD_CHARACTER_PACKAGE_H

#include <string>
#include <vector>


#include "Ogre/Ogre.h"
#include "Package.h"


namespace Charanis {

/**
 * \brief Paket zum Hinzufügen eines neuen Charakters.
 *
 * Dieses Paket teilt dem RenderingLayer mit, ein Character-Objekt für einen neuen Charakter in der Szene anzulegen.
 */
class AddCharacterPackage : public Package {
	private:
		std::string characterName;
		std::string meshName;
		Ogre::Vector3* position;
		Ogre::Vector3* direction;
		Ogre::Real scale;
		
		std::vector<std::string>* femlFiles;
		
	public:
		AddCharacterPackage(std::string characterName, std::string meshName, Ogre::Vector3* position, Ogre::Vector3* direction, Ogre::Real scale=1);
		~AddCharacterPackage();
		
		void addFEMLFile(std::string femlFile);
		
		std::vector<std::string>* getFEMLFiles();
		
		std::string getCharacterName();
		std::string getMeshName();
		Ogre::Vector3* getPosition();
		Ogre::Vector3* getDirection();
		Ogre::Real getScale();
};

} // end of namespace
#endif