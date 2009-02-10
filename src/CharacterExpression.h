/*
 *  CharacterExpression.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 26.05.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef CHARACTER_EXPRESSION_H
#define CHARACTER_EXPRESSION_H

// dependency includes
#ifdef OSX
    #include <Ogre/OgrePrerequisites.h>
#else
    #include <OgrePrerequisites.h>
#endif
// project includes
#include "StringIntMap.h"

namespace Ogre {
class VertexPoseKeyFrame;
} // end of namespace Ogre

namespace Charanis {

class FacialExpression;

class CharacterExpression {
	private:
		FacialExpression* expression;
		Ogre::Real weight;
		Ogre::Real time;
		
	public:
		CharacterExpression(Ogre::Real time, FacialExpression* expression, Ogre::Real weight);
		~CharacterExpression();
		
		FacialExpression* getExpression();
		Ogre::Real getWeight();
		Ogre::Real getTime();
		
		void fillKeyFrame(Ogre::VertexPoseKeyFrame* kf, StringIntMap* poseMapping);
		//fillKeyFrame(Ogre::speechKeyFrame, speechVolume);
};

} // end of namespace

#endif
