/*
 *  TimedEyePositionMap.h
 *  Charanis
 *
 *  Created by Holger Biehl on 20.11.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef TIMED_EYE_POSITION_MAP_H
#define TIMED_EYE_POSITION_MAP_H

#include <map>

#include "Ogre/Ogre.h"
#include "EyePosition.h"

namespace Charanis {
	typedef std::map<Ogre::Real, EyePosition*> TimedEyePositionMap;
} // end of namespace

#endif