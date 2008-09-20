/*
 *  BehaviorLibrary.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 17.05.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef BEHAVIOR_LIBRARY_H
#define BEHAVIOR_LIBRARY_H

// std includes
#include <string>

// project includes
#include "ActionLibrary.h"
#include "BodyAnimationLibrary.h"
#include "ExpressionLibrary.h"


namespace Charanis {

class BehaviorLibrary {
	private:
		std::string characterName;
		ExpressionLibrary expressionLib;
		BodyAnimationLibrary bodyAnimationLib;
		ActionLibrary actionLib;
	
	public:
		BehaviorLibrary(std::string characterName);
		~BehaviorLibrary();
		
		
		std::string getCharacterName();
		
		ExpressionLibrary* getExpressionLibrary();
		FacialExpression* getExpression(std::string expressionName);
		FacialExpression* getExpression(EmotionType emotionType);
		void addExpression(FacialExpression* exp);
		
		BodyAnimationLibrary* getBodyAnimationLibrary();
		BodyAnimation* getBodyAnimation(std::string animationName);
		void addBodyAnimation(BodyAnimation* anim);
		void printBodyAnimations();
		
		ActionScript* getActionScript(std::string actionName);
		void addActionScript(ActionScript* action);
		void printActionScripts();
};

} // end of namespace

#endif
