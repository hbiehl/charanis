/*
 *  CharacterDataPackage.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 01.04.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef CHARACTER_DATA_PACKAGE
#define CHARACTER_DATA_PACKAGE

// std includes
#include <map>
#include <vector>
#include <string>

// dependency includes
#include <Ogre/OgrePrerequisites.h>

// project includes
#include "CharacterExpressionMap.h"
#include "CharacterPerformance.h"
#include "CharacterPerformanceVector.h"
#include "CharacterPerformanceMap.h"
#include "ExpressionMap.h"
#include "ExpressionVector.h"
#include "EyeAnimation.h"
#include "EyeAnimationVector.h"
#include "FKPerformance.h"
#include "FKPerformanceMap.h"
#include "FKPerformanceVector.h"
#include "Package.h"

namespace Charanis {

/**
 * \brief Paket zur Übertragung von Bewegungsinformationen der Charaktere zum RenderingLayer.
 *
 * Dieses Paket ist dafür zuständig, Bewegungsinformationen zu den Charakteren zu übertragen.
 * Ein solches Paket bezieht sich immer auf genau einen Charakter. Nachdem das Paket vom MessageParser erzeugt
 * wurde, wird es in die %Pipeline des entsprechenden Charakters geschoben, durchläuft die %Pipeline und wird
 * schließlich an den RenderingLayer übergeben, der dann für die Anzeige der enthaltenen Daten sorgt.
 */
class CharacterDataPackage : public Package {
	private:
		std::string characterName;
	
		CharacterPerformanceVector* characterPerformanceVector;
		FKPerformanceVector* fkPerformanceVector;
		
		
		//EyeAnimationVector* leftEyeAnimationVector;
		//EyeAnimationVector* rightEyeAnimationVector;
		
		
		/*
		CharacterExpressionMap* characterSpeechExpressionMap;
		CharacterExpressionMap* controlledExpressionMap;
		*/
		TimedExpressionMap* characterSpeechExpressionMap;
		TimedExpressionMap* controlledExpressionMap;
		
		Ogre::Real startTime;
		Ogre::Real endTime;
		//Ogre::Real length;
		
		bool quitProgram;
		
	public:
		CharacterDataPackage(std::string characterName, Ogre::Real startTime, Ogre::Real endTime);
		~CharacterDataPackage();
		
		std::string getCharacterName();
		
		Ogre::Real getStartTime();
		Ogre::Real getEndTime();
		Ogre::Real getLength();
		
		bool getQuitProgram();
		void setQuitProgram(bool quitProgram);
		
		/*
		EyeAnimationVector* getLeftEyeAnimationVector();
		void addLeftEyeAnimation(EyeAnimation* eyeAnim);
		
		EyeAnimationVector* getRightEyeAnimationVector();
		void addRightEyeAnimation(EyeAnimation* eyeAnim);
		*/
		
		CharacterPerformanceVector* getAllCharacterPerformances();
		void addCharacterPerformance(CharacterPerformance* performance);
		
		FKPerformanceVector* getAllFKPerformances();		
		void addFKPerformance(FKPerformance* performance);
		
		TimedExpressionMap* getAllSpeechExpressions();
		void addSpeechExpression(CharacterExpression* exp);
		
		TimedExpressionMap* getAllControlledExpressions();
		void addControlledExpression(CharacterExpression* exp);
};

} // end of namespace

#endif