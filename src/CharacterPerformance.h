/*
 *  CharacterPerformance.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 09.04.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef CHARACTER_PERFORMANCE_H
#define CHARACTER_PERFORMANCE_H

// std includes
#include <map>
#include <string>

// dependency includes
#ifdef OSX
    #include <Ogre/OgrePrerequisites.h>
#else
    #include <OgrePrerequisites.h>
#endif

namespace Charanis {

/**
 * \brief Repräsentation eines Skelettanimations-Kommandos.
 *
 * Diese Klasse beinhaltet ein einzelnes Skelettanimations-Kommando. Sie benennt eine Skelettanimation, die abgespielt werden soll, 
 * sowie einige Parameter zum Timing. Die abzuspielende	Animation muss dem System bereits bekannt sein.
 */

class CharacterPerformance {
	private:
		std::string characterName;
		std::string animationName;
		
		Ogre::Real startTime;
		Ogre::Real endTime;
		
		Ogre::Real intensity;
		Ogre::Real speedModifier;
		
		Ogre::Real fadeinTime;
		Ogre::Real fadeoutTime;
		Ogre::Real startOffsetTime;
		
		bool manualPerformance;
		
		typedef std::map<std::string, Ogre::Real> CharacterPropertyMap;		
		CharacterPropertyMap properties;
		
	public:
		CharacterPerformance(std::string characterName, std::string animationName, Ogre::Real startTime, Ogre::Real endTime, Ogre::Real speedModifier=1);
		CharacterPerformance(std::string characterName, std::string animationName, Ogre::Real startTime, Ogre::Real startOffsetTime, Ogre::Real fadeinTime, Ogre::Real endTime, Ogre::Real fadeoutTime, Ogre::Real speedModifier=1);

		~CharacterPerformance();
		
		void init(std::string characterName, std::string animationName, Ogre::Real startTime, Ogre::Real endTime, Ogre::Real speedModifier);
		
		std::string getCharacterName();
		
		Ogre::Real getStartTime();
		Ogre::Real getEndTime();
		Ogre::Real getSpeedModifier();
		
		Ogre::Real getProperty(std::string property);
		
		
		
		void setCharacterName(std::string characterName);
		
		void getStartTime(Ogre::Real startTime);
		void getEndTime(Ogre::Real endTime);
	
		void setProperty(std::string property, Ogre::Real value);
		
		
		Ogre::Real getFadeinTime();
		Ogre::Real getFadeoutTime();
		Ogre::Real getStartOffsetTime();
		
		void setFadeinTime(Ogre::Real fadeinTime);
		void setFadeoutTime(Ogre::Real fadeoutTime);
		void setStartOffsetTime(Ogre::Real startOffsetTime);
		
		void setIntensity(Ogre::Real intensity);
		Ogre::Real getIntensity();
		
		void setManualPerformance(bool b);
		bool isManualPerformance();
		
		/**
			Gibt true zurück, falls Animation noch nicht beendet wurde, ansonsten false.
		 **/
		//void executeAnimation(Ogre::Real time);
		
		bool isFinished(Ogre::Real time);
		
		std::string getAnimationName();

		CharacterPerformance* cutPerformance(Ogre::Real time);
};

} // end of namespace
#endif
