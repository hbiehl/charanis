/*
 *  FacialExpression.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 11.05.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#include "FacialExpression.h"

// std includes
#include <iostream>
// dependency includes
#include <Ogre/OgreKeyFrame.h>

namespace Charanis {

FacialExpression::FacialExpression(std::string expressionName) {
	//std::cout << "///////////////////////// FacialExpression::FacialExpression("<< expressionName <<") - BEGIN" << std::endl;
	this->expressionName = expressionName;
	
	//std::cout << "///////////////////////// FacialExpression::FacialExpression() ("<< expressionName <<")- END" << std::endl;
}


FacialExpression::~FacialExpression() {
	//std::cout << "///////////////////////// FacialExpression::~FacialExpression() ("<< expressionName <<")" << std::endl;
}
		

std::string FacialExpression::getExpressionName() {
	return expressionName;
}


void FacialExpression::setPoseWeight(std::string poseName, Ogre::Real weight) {
	poseWeightMap[poseName] = weight;
}



Ogre::Real FacialExpression::getPoseWeight(std::string poseName) {
	return poseWeightMap[poseName];
}


void FacialExpression::fillKeyFrame(Ogre::VertexPoseKeyFrame* kf, StringIntMap* poseMapping, Ogre::Real weight) {
	for (StringIntMap::iterator it=poseMapping->begin(); it!=poseMapping->end(); it++) {
		kf->updatePoseReference(it->second, weight*poseWeightMap[it->first]);
	}
}

Ogre::VertexPoseKeyFrame* FacialExpression::createKeyFrame(Ogre::VertexAnimationTrack* track, StringIntMap* poseMapping, Ogre::Real time) {
	Ogre::VertexPoseKeyFrame* kf = track->createVertexPoseKeyFrame(time);
	for (StringIntMap::iterator it=poseMapping->begin(); it!=poseMapping->end(); it++) {
		kf->updatePoseReference(it->second, poseWeightMap[it->first]);
	}
	return kf;
}


void FacialExpression::print() {
	std::cout << "########################### FACIAL_EXPRESSION " << expressionName << "###########################" << std::endl;
	for (StringRealMap::iterator it=poseWeightMap.begin(); it!=poseWeightMap.end(); it++) {
		std::cout << "#############" << it->first << " -> " << it->second << std::endl;
	}
}

} // end of namespace