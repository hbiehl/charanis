/*
 *  FacialExpression.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 11.05.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef FACIAL_EXPRESSION_H
#define FACIAL_EXPRESSION_H

#include <vector>
#include "SDL/SDL.h"
#include <Ogre/Ogre.h>

#include "StringRealMap.h"
#include "StringIntMap.h"

namespace Charanis {

class FacialExpression {
	private:
		std::string expressionName;

		StringRealMap poseWeightMap; //Key: PoseName, Value: Weight
	public:
		FacialExpression(std::string expressionName);
		~FacialExpression();
		
		std::string getExpressionName();

		void setPoseWeight(std::string poseName, Ogre::Real weight);
		Ogre::Real getPoseWeight(std::string poseName);
		
		void fillKeyFrame(Ogre::VertexPoseKeyFrame* kf, StringIntMap* poseMapping, Ogre::Real weight);
		
		Ogre::VertexPoseKeyFrame* createKeyFrame(Ogre::VertexAnimationTrack* track, StringIntMap* poseMapping, Ogre::Real time);
		
		void print();
};

} // end of namespace

#endif