/*
 *  DataManager.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 07.04.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "DataManager.h"
#include <limits.h>

namespace Charanis {

DataManager::DataManager() : engineTime(0) , manualAnimationId(0) {
	std::cout << "§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§ DataManager::DataManager()" << std::endl;
	config = new Config("../../config.xml");

	boost::mt19937 rng;
	rng.seed(static_cast<unsigned int>(std::time(0)));
	boost::uniform_int<> hundred(0,100);
	d100 = new boost::variate_generator<boost::mt19937, boost::uniform_int<> >(rng, hundred);

	boost::mt19937 rng2;
	rng2.seed(static_cast<unsigned int>(std::time(0)));
	boost::uniform_real<> alpha(0,1);
	rAlpha = new boost::variate_generator<boost::mt19937, boost::uniform_real<> >(rng2, alpha);
	std::cout << "§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§ DataManager::DataManager()" << std::endl;
}

DataManager::~DataManager() {
	std::cout << "§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§ DataManager::~DataManager() - BEGIN" << std::endl;
	/*
	for (CharacterDataMap::iterator it = characterDataMap.begin(); it!=characterDataMap.end(); it++) {
		delete it->second;
	}
	characterDataMap.clear();
	*/
	while (characterDataMap.size() > 0) {
		delete characterDataMap.begin()->second;
		characterDataMap.erase(characterDataMap.begin()->first);
	}
	
	
	/*
	for (BehaviorLibraryMap::iterator it = behaviorLibMap.begin(); it!=behaviorLibMap.end(); it++) {
		delete it->second;
	}
	behaviorLibMap.clear();
	*/
	while (behaviorLibMap.size()>0) {
		delete behaviorLibMap.begin()->second;
		behaviorLibMap.erase(behaviorLibMap.begin()->first);
	}
	
	delete config;
	std::cout << "§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§ DataManager::~DataManager() - END" << std::endl;
}



Config* DataManager::getConfig() {
	return config;
}


void DataManager::addCharacter(std::string characterName) {
	std::cout << "§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§ DataManager::addCharacter("<< characterName <<")  BEGIN" << std::endl;
	queueTimeMap[characterName] = getEngineTime();
	behaviorLibMap[characterName] = new BehaviorLibrary(characterName);
	characterDataMap[characterName] = new CharacterData();
	std::cout << "§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§ DataManager::addCharacter("<< characterName <<")  END" << std::endl;
}


void DataManager::removeCharacter(std::string characterName) {
	std::cout << "DataManager::removeCharacter(" << characterName << ")   BEGIN" << std::endl;
	if (queueTimeMap.find(characterName) != queueTimeMap.end()) {
		queueTimeMap.erase(queueTimeMap.find(characterName));
	}
	
	if (characterDataMap.find(characterName)!=characterDataMap.end()) {
		delete characterDataMap[characterName];
		characterDataMap.erase(characterName);	
	}
	if (behaviorLibMap.find(characterName)!=behaviorLibMap.end()) {
		delete behaviorLibMap[characterName];
		behaviorLibMap.erase(characterName);	
	}
	std::cout << "DataManager::removeCharacter(" << characterName << ")   END" << std::endl;
}


BehaviorLibrary* DataManager::getBehaviorLibrary(std::string characterName) {
	if (behaviorLibMap.find(characterName) != behaviorLibMap.end()) {
		return behaviorLibMap[characterName];
	} else {
		return NULL;
	}

}


unsigned int DataManager::nextManualAnimationId() {
	if (manualAnimationId<UINT_MAX) {
		manualAnimationId++;
	} else {
		manualAnimationId = 0;
	}
	
	return manualAnimationId;
}

		
Ogre::Real DataManager::getEmotion(std::string characterName, EmotionType type, Ogre::Real time) {
	if (characterDataMap.find(characterName) != characterDataMap.end()) {
		return characterDataMap[characterName]->getEmotion(type, time);
	} else {
		// TODO: throw Exception
		return -1;
	}
}


void DataManager::setEmotion(std::string characterName, EmotionType type, Ogre::Real time, Ogre::Real value) {
	if (characterDataMap.find(characterName) != characterDataMap.end()) {
		characterDataMap[characterName]->setEmotion(type, time, value);
	} else {
		// TODO: throw Exception
	}
}


void DataManager::addQueueTime(std::string characterName, Ogre::Real time) {
	boost::mutex::scoped_lock lock(queueTimeMutex);
	if (queueTimeMap.find(characterName) != queueTimeMap.end()) {
		queueTimeMap[characterName] += time;
	}
	std::cout << "DataManager - new QueueTime for " << characterName << " is " << queueTimeMap[characterName] << std::endl;
}

Ogre::Real DataManager::getQueueTime(std::string characterName) {
	boost::mutex::scoped_lock lock(queueTimeMutex);
	Ogre::Real queueTime = 0;
	if (queueTimeMap.find(characterName) != queueTimeMap.end()) {
		queueTime = queueTimeMap[characterName];
	}
	return queueTime;
}


void DataManager::setEngineTime(Ogre::Real time) {
	boost::mutex::scoped_lock lock(engineTimeMutex);
	engineTime = time;
}

Ogre::Real DataManager::getEngineTime() {
	boost::mutex::scoped_lock lock(engineTimeMutex);
	return engineTime;
}


int DataManager::random100() {
	return (*d100)();
}

Ogre::Real DataManager::randomAlpha() {
	return (*rAlpha)();
}

} // end of namespace