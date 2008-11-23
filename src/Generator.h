/*
 *  Generator.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 10.11.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef GENERATOR_H
#define GENERATOR_H


#include <climits>

#include <string>
#include <iostream>


#include "DataManager.h"
#include "CharacterDataPackage.h"

namespace Charanis {

/** 
 * \brief Basisklasse für Generatoren zur automatischen Animationserzeugung.
 * 
 * Der AnimationGenerationLayer ist für die Erzeugung von automatischer Animation zuständig. Dafür bindet er eine Reihe
 * von Generatoren ein, die alle von dieser Basisklasse abgeleitet sind.
 */
class Generator {
	private:
		DataManager* dataManager;
		std::string characterName;
		std::string generatorName;
		
		unsigned long animationNo;
		
	protected:
		std::string generateAnimationName();
		
	public:
		Generator(DataManager* dataManager, std::string characterName, std::string generatorName);
		~Generator();
		
		DataManager* getDataManager();
		std::string getCharacterName();
		std::string getGeneratorName();
		virtual void execute(CharacterDataPackage* pkg);
};

} // end of namespace

#endif