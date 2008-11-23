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

#include <map>


#include "Ogre/Ogre.h"

#include "FKKeyFrame.h"

namespace Charanis {
	typedef std::map<Ogre::Real, FKKeyFrame*> FKKeyFrameMap;
} // end of namespace
#endif