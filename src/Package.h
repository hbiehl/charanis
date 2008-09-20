/*
 *  Package.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 17.08.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef PACKAGE_H
#define PACKAGE_H

namespace Charanis {

/**
 * \brief Basisklasse der internen Kommunikations-Pakete.
 *
 * Die interne Kommunikation zwischen den einzelnen Charanis-Komponenten geschieht über
 * Pakete und Queue s. Für verschiedene Inhalte stehen auch unterschiedliche Pakettypen 
 * zur Verfügung. Alle Pakete sind jedoch von dieser Klasse abgeleitet.
 */
class Package {
	public:
		enum PackageType {
			CHARACTER_DATA_PACKAGE_TYPE,
			ADD_CHARACTER_PACKAGE_TYPE,
			REMOVE_CHARACTER_PACKAGE_TYPE,
			IMPORT_FEML_FILE_PACKAGE_TYPE,
			IMPORT_SAML_FILE_PACKAGE_TYPE,
			CHARACTER_SOUND_PACKAGE_TYPE,
			ADD_OBJECT_PACKAGE_TYPE,
			REMOVE_OBJECT_PACKAGE_TYPE,
			CAMERA_CONTROL_PACKAGE_TYPE,
			AMBIENT_LIGHT_PACKAGE_TYPE,
			DIRECTIONAL_LIGHT_PACKAGE_TYPE,
			REMOVE_DIRECTIONAL_LIGHT_PACKAGE_TYPE,
			SCENE_PACKAGE_TYPE,
			SYSTEM_PACKAGE_TYPE};
		
	
	
	
	protected:
		PackageType type;
		//unsigned long id;
	
	public:			
		Package(PackageType type);//, unsigned long id);
		~Package();
		
		PackageType getType();
		//unsigned long getId();
};

} // end of namespace

#endif
