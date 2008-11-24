/*
 *  AnimationPackage.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 01.04.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#include "CharacterDataPackage.h"

// project includes
#include "CharacterExpression.h"

namespace Charanis {

CharacterDataPackage::CharacterDataPackage(std::string characterName, Ogre::Real startTime, Ogre::Real endTime) 
: Package(CHARACTER_DATA_PACKAGE_TYPE) {
	this->characterName = characterName;
	this->startTime = startTime;
	this->endTime = endTime;
	//this->length = length;
	characterPerformanceVector = new CharacterPerformanceVector();
	fkPerformanceVector = new FKPerformanceVector();
	characterSpeechExpressionMap = new TimedExpressionMap();
	controlledExpressionMap = new TimedExpressionMap();
	
	//leftEyeAnimationVector = new EyeAnimationVector();
	//rightEyeAnimationVector = new EyeAnimationVector();
	
	//speechExpressions = new ExpressionVector();
}


CharacterDataPackage::~CharacterDataPackage() {
	std::cout << "%%% Desctructor CharacterDataPackage - BEGIN %%%" << std::endl;
	// TODO: clear and delete CharacterPerformanceMap?!?
	// TODO: clear and delete fkPerformanceMap?
	// TODO: clear and delete speechExpressions?
	// TODO: clear and delete controlledExpressions?
	// TODO: clear and delete leftEyeAnimationVector?
	// TODO: clear and delete rightEyeAnimationVector?
	std::cout << "%%% Desctructor CharacterDataPackage - END %%%" << std::endl;
}

/*
EyeAnimationVector* CharacterDataPackage::getLeftEyeAnimationVector() {
	return leftEyeAnimationVector;
}

void CharacterDataPackage::addLeftEyeAnimation(EyeAnimation* eyeAnim) {
	leftEyeAnimationVector->push_back(eyeAnim);
}

EyeAnimationVector* CharacterDataPackage::getRightEyeAnimationVector() {
	return rightEyeAnimationVector;
}

void CharacterDataPackage::addRightEyeAnimation(EyeAnimation* eyeAnim) {
	rightEyeAnimationVector->push_back(eyeAnim);
}
*/


std::string CharacterDataPackage::getCharacterName() {
	return characterName;
}
	

Ogre::Real CharacterDataPackage::getStartTime() { 
	return startTime;
}

Ogre::Real CharacterDataPackage::getEndTime() {
	return endTime;
}


Ogre::Real CharacterDataPackage::getLength() {
	return (endTime - startTime);
}


bool CharacterDataPackage::getQuitProgram() {
	return quitProgram;
}


void CharacterDataPackage::setQuitProgram(bool quitProgram) {
	this->quitProgram = quitProgram;
}


/*
CharacterPerformance* CharacterDataPackage::getCharacterPerformance(std::string characterName) {
	if (characterPerformances.find(characterName) != characterPerformances.end()) {
		return characterPerformances[characterName];
	} else {
		return NULL;
	}
}


CharacterPerformanceVector* CharacterDataPackage::getAllCharacterPerformances() {
	CharacterPerformanceVector* performanceVec = new CharacterPerformanceVector();
	for (CharacterPerformanceMap::iterator it = characterPerformances.begin(); it != characterPerformances.end(); it++) {
		performanceVec->push_back(it->second);
	}
	return performanceVec;
}
*/

CharacterPerformanceVector* CharacterDataPackage::getAllCharacterPerformances() {
	return characterPerformanceVector;
}	


void CharacterDataPackage::addCharacterPerformance(CharacterPerformance* performance) {
	characterPerformanceVector->push_back(performance);
}


FKPerformanceVector* CharacterDataPackage::getAllFKPerformances() {
	return fkPerformanceVector;
}

/*		
FKPerformanceVector* CharacterDataPackage::getFKPerformances(std::string characterName) {
	FKPerformanceMap::iterator pos = fkPerformanceMap->find(characterName);
    if (pos != fkPerformanceMap->end()) {
		return (*fkPerformanceMap)[characterName];
	} else {
		return NULL;
	}
}
*/

void CharacterDataPackage::addFKPerformance(FKPerformance* performance) {
	fkPerformanceVector->push_back(performance);
	/*std::string characterName = performance->getCharacterName();
	FKPerformanceMap::iterator pos = fkPerformanceMap->find(characterName);
    if (pos != fkPerformanceMap->end()) {
		(*fkPerformanceMap)[characterName]->push_back(performance);
	} else {
		(*fkPerformanceMap)[characterName] = new FKPerformanceVector();
		(*fkPerformanceMap)[characterName]->push_back(performance);
	}
	*/
}



TimedExpressionMap* CharacterDataPackage::getAllSpeechExpressions() {
	return characterSpeechExpressionMap;
}


void CharacterDataPackage::addSpeechExpression(CharacterExpression* exp) {
	(*characterSpeechExpressionMap)[exp->getTime()] = exp;
}



TimedExpressionMap* CharacterDataPackage::getAllControlledExpressions() {
	return controlledExpressionMap;
}

void CharacterDataPackage::addControlledExpression(CharacterExpression* exp) {
	(*controlledExpressionMap)[exp->getTime()] = exp;
}

} // end of namespace