/*
 *  BehaviorLibrary.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 17.05.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "BehaviorLibrary.h"


namespace Charanis {

BehaviorLibrary::BehaviorLibrary(std::string characterName) :
expressionLib(characterName), bodyAnimationLib(characterName), actionLib(characterName) {
	std::cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& BehaviorLibrary::BehaviorLibrary() ("<< characterName <<") - BEGIN" << std::endl;
	this->characterName = characterName;
	std::cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& BehaviorLibrary::BehaviorLibrary() ("<< characterName <<") - END" << std::endl;
}



BehaviorLibrary::~BehaviorLibrary() {
	std::cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& BehaviorLibrary::~BehaviorLibrary() ("<< characterName << ") - BEGIN" << std::endl;
	// expressionLib gerät out of scope und wird damit automatisch gelöscht 
	// bodyAnimationLib gerät out of scope und wird damit automatisch gelöscht
	// actionLib gerät out of scope und wird damit automatisch gelöscht
	std::cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& BehaviorLibrary::~BehaviorLibrary() ("<< characterName << ") - END" << std::endl;
}

		
		
std::string BehaviorLibrary::getCharacterName() {
	return characterName;
}


ExpressionLibrary* BehaviorLibrary::getExpressionLibrary() {
	return &expressionLib;
}


FacialExpression* BehaviorLibrary::getExpression(std::string expressionName) {
	return expressionLib.getExpression(expressionName);
}


FacialExpression* BehaviorLibrary::getExpression(EmotionType emotionType) {
	return expressionLib.getExpression(expressionLib.emotionExpressionMapping[emotionType]);
}


void BehaviorLibrary::addExpression(FacialExpression* exp) {
	expressionLib.addExpression(exp);
}




BodyAnimationLibrary* BehaviorLibrary::getBodyAnimationLibrary() {
	return &bodyAnimationLib;
}

BodyAnimation* BehaviorLibrary::getBodyAnimation(std::string animationName) {
	return bodyAnimationLib.getBodyAnimation(animationName);
}

void BehaviorLibrary::addBodyAnimation(BodyAnimation* anim) {
	bodyAnimationLib.addBodyAnimation(anim);
}

void BehaviorLibrary::printBodyAnimations() {
	bodyAnimationLib.print();
}




ActionScript* BehaviorLibrary::getActionScript(std::string actionName) {
	return actionLib.getActionScript(actionName);
}

void BehaviorLibrary::addActionScript(ActionScript* action) {
	actionLib.addActionScript(action);
}

void BehaviorLibrary::printActionScripts() {
	actionLib.print();
}

} // end of namespace