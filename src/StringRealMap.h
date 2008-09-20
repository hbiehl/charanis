/*
 *  StringRealMap.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 13.08.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef STRING_REAL_MAP_H
#define STRING_REAL_MAP_H

// std includes
#include <map>
#include <string>

// dependency includes
#ifdef OSX
    #include <Ogre/OgrePrerequisites.h>
#else
    #include <OgrePrerequisites.h>
#endif

namespace Charanis {
	typedef std::map<std::string, Ogre::Real> StringRealMap;
} // end of namespace

#endif
