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

// std includes
#include <map>

// dependency includes
#ifdef OSX
    #include <Ogre/OgrePrerequisites.h>
#else
    #include <OgrePrerequisites.h>
#endif

namespace Charanis {
class EyePosition;
typedef std::map<Ogre::Real, EyePosition*> TimedEyePositionMap;
} // end of namespace

#endif
