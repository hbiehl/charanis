/*
 *  FKKeyFrameMap.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 26.07.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef FK_KEY_FRAME_MAP_H
#define FK_KEY_FRAME_MAP_H

// std includes
#include <map>

// dependency includes
#ifdef OSX
    #include <Ogre/OgrePrerequisites.h>
#else
    #include <OgrePrerequisites.h>
#endif

namespace Charanis {

class FKKeyFrame;
typedef std::map<Ogre::Real, FKKeyFrame*> FKKeyFrameMap;
} // end of namespace
#endif
