/*
 *  CharacterPerformance.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 09.04.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#include "CharacterPerformance.h"

// std includes
#include <iostream>


namespace Charanis {

CharacterPerformance::CharacterPerformance(std::string characterName, std::string animationName, Ogre::Real startTime, Ogre::Real endTime, Ogre::Real speedModifier) {
	std::cout << "==================== CharacterPerformance KONSTRUKTOR: " << characterName << " (" << animationName << "; start="<< startTime <<" end="<< endTime <<")" << std::endl;
	init(characterName, animationName, startTime, endTime, speedModifier);
}

CharacterPerformance::CharacterPerformance(std::string characterName, std::string animationName, Ogre::Real startTime, Ogre::Real startOffsetTime, Ogre::Real fadeinTime, Ogre::Real endTime, Ogre::Real fadeoutTime, Ogre::Real speedModifier) {
	//std::cout << "==================== CharacterPerformance KONSTRUKTOR: " << characterName << " (" << animationName << "; start="<< startTime <<" end="<< endTime <<")" << std::endl;
	init(characterName, animationName, startTime, endTime, speedModifier);
	
	this->startOffsetTime = startOffsetTime;
	this->fadeinTime = fadeinTime;
	this->fadeoutTime = fadeoutTime;
}



CharacterPerformance::~CharacterPerformance() {
	//std::cout << "================== DESTRUCTOR CharacterPerformance " << characterName << "   " << animationName << " -  BEGIN" << std::endl;
	// TODO: clean performanceMap?!?
	//std::cout << "================== DESTRUCTOR CharacterPerformance " << characterName << "   " << animationName << " -  END" << std::endl;
}



void CharacterPerformance::init(std::string characterName, std::string animationName, Ogre::Real startTime, Ogre::Real endTime, Ogre::Real speedModifier) {	
	this->characterName = characterName;
	this->animationName = animationName;
	
	this->startTime = startTime;
	this->endTime = endTime;
	this->speedModifier = speedModifier;
	
	this->startOffsetTime = 0;	
	this->fadeinTime = 0.5;
	this->fadeoutTime = 0.5;
	
	this->intensity = 1;
	
	properties = CharacterPropertyMap();
}





std::string CharacterPerformance::getCharacterName() {
	return characterName;
}




Ogre::Real CharacterPerformance::getStartTime() {
	return startTime;
}



Ogre::Real CharacterPerformance::getEndTime() {
	return endTime;
}



Ogre::Real CharacterPerformance::getProperty(std::string property) {
	if (properties.find(property) != properties.end()) {
		return properties[property];
	} else {
		// Throw Exception: PropertyNotFoundException
	}
}



void CharacterPerformance::setCharacterName(std::string characterName) {
	this->characterName = characterName;
}



void CharacterPerformance::getStartTime(Ogre::Real startTime) {
	this->startTime = startTime;
}



void CharacterPerformance::getEndTime(Ogre::Real endTime) {
	this->endTime = endTime;
}

Ogre::Real CharacterPerformance::getSpeedModifier() {
	return speedModifier;
}


void CharacterPerformance::setProperty(std::string property, Ogre::Real value) {
	properties[property] = value;
}



Ogre::Real CharacterPerformance::getFadeinTime() {
	return fadeinTime;
}


Ogre::Real CharacterPerformance::getFadeoutTime() {
	return fadeoutTime;
}


Ogre::Real CharacterPerformance::getStartOffsetTime() {
	return startOffsetTime;
}


void CharacterPerformance::setFadeinTime(Ogre::Real fadeinTime) {
	this->fadeinTime = fadeinTime;
}

void CharacterPerformance::setFadeoutTime(Ogre::Real fadeoutTime) {
	this->fadeoutTime = fadeoutTime;
}


void CharacterPerformance::setStartOffsetTime(Ogre::Real startOffsetTime) {
	this->startOffsetTime = startOffsetTime;
}


void CharacterPerformance::setIntensity(Ogre::Real intensity) {
	this->intensity = intensity;
}

Ogre::Real CharacterPerformance::getIntensity() {
	return intensity;
}


void CharacterPerformance::setManualPerformance(bool b) {
	manualPerformance = b;
}

bool CharacterPerformance::isManualPerformance() {
	return manualPerformance;
}


/**
	Gibt true zurück, falls Animation noch nicht beendet wurde, ansonsten false.
 **/
//void executeAnimation(Ogre::Real time);

bool CharacterPerformance::isFinished(Ogre::Real time) {
	return (time > endTime);
}

std::string CharacterPerformance::getAnimationName() {
	return animationName;
}



CharacterPerformance* CharacterPerformance::cutPerformance(Ogre::Real time) {
	CharacterPerformance* performance = NULL;
	// Schnitt nur innerhalb der "vollen" Wirkung der Animation - während fadein oder fadeout wird nicht geschnitten.
	// Damit wird innerhalb dieser Zeit auch keine Kollisionsbehandlung vollzogen...
	if (time>(startTime+fadeinTime) && time<(endTime-fadeoutTime)) {
		std::cout << "CUTTING PERFORMANCE - BEGIN" << std::endl;
		Ogre::Real cutOffsetTime = startOffsetTime + (time-startTime);
		
		// Neue "Restperformance"
		performance = new CharacterPerformance(characterName, animationName, time, cutOffsetTime, fadeinTime, endTime, fadeoutTime, speedModifier);
		std::cout << "Rest: startTime=" << performance->getStartTime() << "   endTime=" << performance->getEndTime() << std::endl;
		
		// diese Performance entsprechend kürzen
		fadeoutTime = 0;
		endTime = time;
		std::cout << "CUTTING PERFORMANCE [DONE]" << std::endl;
	}
	return performance;
}

} // end of namespace