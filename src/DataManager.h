/*
 *  DataManager.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 07.04.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

// std includes
#include <map>
#include <string>
// dependency includes
#include <boost/thread/thread.hpp>
#include <boost/random.hpp>
//#include <boost/random/linear_congruential.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
#include <Ogre/OgrePrerequisites.h>
// project includes
#include "EmotionTypes.h"


namespace Charanis {

class BehaviorLibrary;
class CharacterData;
class Config;

/**
 * \brief Zentrale Klasse zum Verwalten verschiedenster Daten.
 *
 * Dies ist eine zentrale Instanz zum Verwalten verschiedenster Daten. Alle Stufen der Charakter-Pipelines, sowie die Eingabe-
 * und Ausgabe-Komponente haben Zugriff auf den DataManager. Damit es bei parallelen Zugriffen keine Laufzeitfehler gibt,
 * sind die Zugriffe auf die Attribute mit Semaphoren gesch\"utzt, ebenso die Zugriffe auf diverse Hilfsklassen des DataManagers. 
 * 
 * Der Eigentümer des DataManager-Objektes ist der EngineManager - von diesem wird also die Instanz erzeugt und auch wieder gelöscht.
 *
 */

class DataManager {
	private:
		typedef std::map<std::string, CharacterData*> CharacterDataMap;
		CharacterDataMap characterDataMap;
	
		typedef std::map<std::string, BehaviorLibrary*> BehaviorLibraryMap;
		BehaviorLibraryMap behaviorLibMap;
		
		unsigned int manualAnimationId;
		
		Ogre::Real engineTime;
		boost::mutex engineTimeMutex;
		
		std::map<std::string, Ogre::Real> queueTimeMap; // key: characterName, value: time
		boost::mutex queueTimeMutex;
		
		Config* config;
		
		
		boost::variate_generator<boost::mt19937, boost::uniform_int<> >* d100;
		boost::variate_generator<boost::mt19937, boost::uniform_real<> >* rAlpha;
		
		
	public:
		DataManager();
		~DataManager();
		
		Config* getConfig();
		
		void addCharacter(std::string characterName);
		void removeCharacter(std::string characterName);
		
		BehaviorLibrary* getBehaviorLibrary(std::string characterName);
		
		unsigned int nextManualAnimationId();
		
		Ogre::Real getEmotion(std::string characterName, EmotionType type, Ogre::Real time);
		void setEmotion(std::string characterName, EmotionType type, Ogre::Real time, Ogre::Real value);
		
		void addQueueTime(std::string characterName, Ogre::Real time);
		Ogre::Real getQueueTime(std::string characterName);

		void setEngineTime(Ogre::Real time);
		Ogre::Real getEngineTime();
		
		int random100();
		Ogre::Real randomAlpha();
};

} // end of namespace

#endif
