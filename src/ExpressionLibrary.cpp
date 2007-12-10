/*
 *  ExpressionLibrary.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 17.05.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "ExpressionLibrary.h"


namespace Charanis {

ExpressionLibrary::ExpressionLibrary(std::string characterName) {
	std::cout << "??????????????????????????????? ExpressionLibrary::ExpressionLibrary() ("<< characterName <<") - BEGIN" << std::endl;
	this->characterName = characterName;
	poseMapping = new StringIntMap();
	
	emotionExpressionMapping[EMOTION_JOY]		= "joy";
	emotionExpressionMapping[EMOTION_SADNESS]	= "sadness";
	emotionExpressionMapping[EMOTION_ANGER]		= "anger";
	emotionExpressionMapping[EMOTION_DISGUST]	= "disgust";
	emotionExpressionMapping[EMOTION_FEAR]		= "fear";
	emotionExpressionMapping[EMOTION_SURPRISE]	= "surprise";
	/*
	EMOTION_JOY,
	EMOTION_SADNESS,
	EMOTION_ANGER,
	EMOTION_DISGUST,
	EMOTION_FEAR,
	EMOTION_SURPRISE,
	*/
	
	
	// Emotional Expressions
	FacialExpression* exp = new FacialExpression("neutral");
	expressionMap["neutral"] = exp;
	
	exp = new FacialExpression("joy");
	exp->setPoseWeight("Expression_happy", 1.0);
	expressionMap["joy"] = exp;
	
	exp = new FacialExpression("sadness");
	exp->setPoseWeight("Expression_sad", 1.0);
	expressionMap["sadness"] = exp;
	
	exp = new FacialExpression("anger");
	exp->setPoseWeight("Expression_mad", 1.0);
	expressionMap["anger"] = exp;
	
	
	exp = new FacialExpression("disgust");
	expressionMap["disgust"] = exp;
	
	exp = new FacialExpression("fear");
	expressionMap["fear"] = exp;
	
	exp = new FacialExpression("surprise");
	expressionMap["surprise"] = exp;
	
	
	
	// Speech-Expressions => Visemes
	exp = new FacialExpression("VISEME_NEUTRAL");
	expressionMap["VISEME_NEUTRAL"] = exp;
	
	exp = new FacialExpression("VISEME_A");
	exp->setPoseWeight("A_ShapeKey", 1.0);
	expressionMap["VISEME_A"] = exp;

	exp = new FacialExpression("VISEME_U");
	exp->setPoseWeight("U_ShapeKey", 1.0);
	expressionMap["VISEME_U"] = exp;

	exp = new FacialExpression("VISEME_O");
	exp->setPoseWeight("O_ShapeKey", 1.0);
	expressionMap["VISEME_O"] = exp;
	
	exp = new FacialExpression("VISEME_E");
	exp->setPoseWeight("E_ShapeKey", 1.0);
	expressionMap["VISEME_E"] = exp;
	
	exp = new FacialExpression("VISEME_I");
	exp->setPoseWeight("I_ShapeKey", 1.0);
	expressionMap["VISEME_I"] = exp;
	
	exp = new FacialExpression("VISEME_C");
	exp->setPoseWeight("C_ShapeKey", 1.0);
	expressionMap["VISEME_C"] = exp;
	
	exp = new FacialExpression("VISEME_W");
	exp->setPoseWeight("W_ShapeKey", 1.0);
	expressionMap["VISEME_W"] = exp;
	
	exp = new FacialExpression("VISEME_M");
	exp->setPoseWeight("M_ShapeKey", 1.0);
	expressionMap["VISEME_M"] = exp;
	
	
	exp = new FacialExpression("VISEME_L");
	exp->setPoseWeight("L_ShapeKey", 1.0);
	expressionMap["VISEME_L"] = exp;
	
	exp = new FacialExpression("VISEME_F");
	exp->setPoseWeight("F_ShapeKey", 1.0);
	expressionMap["VISEME_F"] = exp;
	
	exp = new FacialExpression("VISEME_T");
	exp->setPoseWeight("T_ShapeKey", 1.0);
	expressionMap["VISEME_T"] = exp;
	
	exp = new FacialExpression("VISEME_P");
	exp->setPoseWeight("P_ShapeKey", 1.0);
	expressionMap["VISEME_P"] = exp;
	
	exp = new FacialExpression("VISEME_R");
	exp->setPoseWeight("R_ShapeKey", 1.0);
	expressionMap["VISEME_R"] = exp;
	
	exp = new FacialExpression("VISEME_S");
	exp->setPoseWeight("S_ShapeKey", 1.0);
	expressionMap["VISEME_S"] = exp;
	
	exp = new FacialExpression("VISEME_TH");
	exp->setPoseWeight("TH_ShapeKey", 1.0);
	expressionMap["VISEME_TH"] = exp;
	
	
	std::cout << "??????????????????????????????? ExpressionLibrary::ExpressionLibrary() ("<< characterName <<") - END" << std::endl;
}



ExpressionLibrary::~ExpressionLibrary() {
	std::cout << "??????????????????????????????? ExpressionLibrary::~ExpressionLibrary() ("<< characterName <<") - BEGIN" << std::endl;
	
	delete poseMapping;
	// delete expressions and clear expressionMap
	ExpressionMap::iterator it;
	for (it = expressionMap.begin(); it!=expressionMap.end(); it++) {
		std::cout << "deleting expression " << it->second->getExpressionName() << std::endl;
		delete it->second;
	}
	expressionMap.clear();
	std::cout << "??????????????????????????????? ExpressionLibrary::~ExpressionLibrary() ("<< characterName <<") - END" << std::endl;
}
		

StringIntMap* ExpressionLibrary::getPoseMapping() {
	return poseMapping;
}

void ExpressionLibrary::addPoseMapping(std::string poseName, int poseIndex) {
	(*poseMapping)[poseName] = poseIndex;
}

int ExpressionLibrary::getPoseIndex(std::string poseName) {
	int poseIndex = -1;
	if (poseMapping->find(poseName)!=poseMapping->end()) {
		poseIndex = (*poseMapping)[poseName];
	} else {
		// TODO: throw exception
	}
	return poseIndex;
}


void ExpressionLibrary::addExpression(FacialExpression* exp) {
	if (expressionMap.find(exp->getExpressionName())!=expressionMap.end()) {
		// TODO: throw Exception: 
	} else {
		expressionMap[exp->getExpressionName()] = exp;
	}
}


FacialExpression* ExpressionLibrary::getExpression(std::string expressionName) {
	if (expressionMap.find(expressionName)==expressionMap.end()) {
		return NULL;
	} else {
		return expressionMap[expressionName];
	}
}


void ExpressionLibrary::importExpressionFile(std::string femlDir, std::string fileName) {
	FEMLParser parser = FEMLParser(femlDir);
	
	FacialExpressionVector* feVec = parser.parseFile(fileName);
	for (FacialExpressionVector::iterator it=feVec->begin(); it!=feVec->end(); it++) {
		addExpression(*it);
	}
	feVec->clear();
	delete feVec;
}

std::string ExpressionLibrary::getCharacterName() {
	return characterName;
}

} // end of namespace