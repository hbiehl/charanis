/*
 *  EyeAnimation.cpp
 *  Charanis
 *
 *  Created by Holger Biehl on 20.11.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#include "EyeAnimation.h"
// project includes
#include "EyePosition.h"

namespace Charanis {

EyeAnimation::EyeAnimation() {
	eyePositionMap = new TimedEyePositionMap();
}

EyeAnimation::~EyeAnimation() {
	for (TimedEyePositionMap::iterator it = eyePositionMap->begin(); it!=eyePositionMap->end(); it++) {
		delete it->second;
	}
	eyePositionMap->clear();
	delete eyePositionMap;
}
		
	
int EyeAnimation::getNumKeyFrames() {
	return eyePositionMap->size();
}
				
void EyeAnimation::addEyePosition(EyePosition* eyePosition) {
	(*eyePositionMap)[eyePosition->getTime()] = eyePosition;
}


TimedEyePositionMap* EyeAnimation::getEyePositionMap() {
	return eyePositionMap;
}

} // end of namespace

