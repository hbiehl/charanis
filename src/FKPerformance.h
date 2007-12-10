/*
 *  FKPerformance.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 26.07.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef FK_PERFORMANCE_H
#define FK_PERFORMANCE_H

#include <string>
#include <map>

#include "FKTrack.h"
#include "FKTrackMap.h"

#include "CharacterPerformance.h"

namespace Charanis {


/**
 * \brief Klasse zur Definition von Skelett-Animationen zur Laufzeit.
 *
 * Wie die CharacterPerformance dient die FKPerformance zum Verwalten von Skelettanimations-Kommandos.
 * Allerdings werden hier nicht bereits existierende Animationen angesprochen, sondern die Animationsdefinition
 * innerhalb der Klasse als vorwärtskinematische Anweisungen mitgeliefert (das "FK" im Klassenname steht für
 * "Forward Kinematik").
 */

class FKPerformance {
	private:
		std::string animationName;
		std::string characterName;
		Ogre::Real length;
		
		FKTrackMap fkTrackMap; // boneName -> FKtrack*
	
		CharacterPerformance* characterPerformance;
	
	public:
		FKPerformance(std::string animationName, std::string characterName, Ogre::Real length=0);
		~FKPerformance();
		
		void addTrack(FKTrack* track);
	
		std::string getAnimationName();
	
		std::string getCharacterName();
		void setLength(Ogre::Real length);
		Ogre::Real getLength();
		
		void setCharacterPerformance(CharacterPerformance* characterPerformance);
		CharacterPerformance* getCharacterPerformance();
		
		Ogre::Animation* createOgreAnimation(Ogre::Entity* entity);
};

} // end of namespace

#endif