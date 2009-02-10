/*
 *  ExpressionLibrary.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 17.05.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef EXPRESSION_LIBRARY_H
#define EXPRESSION_LIBRARY_H

// std includes
#include <map>
#include <string>

// project includes
#include "EmotionTypes.h"
#include "ExpressionMap.h"
#include "StringIntMap.h"


namespace Charanis {

class FacialExpression;

class ExpressionLibrary {
	private:
		ExpressionMap expressionMap;
		std::string characterName;
		
		StringIntMap* poseMapping;
	
	public:
		std::map<EmotionType, std::string> emotionExpressionMapping;
	
	
		ExpressionLibrary(std::string characterName);
		~ExpressionLibrary();
		
		StringIntMap* getPoseMapping();
		void addPoseMapping(std::string poseName, int poseIndex);
		int getPoseIndex(std::string poseName);
		
		void addExpression(FacialExpression* exp);
		FacialExpression* getExpression(std::string expressionName);
		
		void importExpressionFile(std::string femlDir, std::string fileName);
		
		std::string getCharacterName();
};

} // end of namespace

#endif
