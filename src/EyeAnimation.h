/*
 *  EyeAnimation.h
 *  Charanis
 *
 *  Created by Holger Biehl on 20.11.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef EYE_ANIMATION_H
#define EYE_ANIMATION_H

#include "SDL/SDL.h"
#include "EyePosition.h"
#include "TimedEyePositionMap.h"

namespace Charanis {

class EyeAnimation {
	private:
		TimedEyePositionMap* eyePositionMap;
		
		
	public:
		EyeAnimation();
		~EyeAnimation();
		
		int getNumKeyFrames();
		
		void addEyePosition(EyePosition* eyePosition);
		TimedEyePositionMap* getEyePositionMap();
};

} // end of namespace

#endif