/*
 *  BodyAnimationMap.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 28.05.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef BODY_ANIMATION_MAP_H
#define BODY_ANIMATION_MAP_H

#include <string>
#include <map>

#include "BodyAnimation.h"


namespace Charanis {
	typedef std::map<std::string, BodyAnimation*> BodyAnimationMap;
} // end of namespace

#endif