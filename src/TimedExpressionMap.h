/*
 *  TimedExpressionMap.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 21.05.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef TIMED_EXPRESSION_MAP_H
#define TIMED_EXPRESSION_MAP_H

#include <map>
#include <string>
#include "CharacterExpression.h"

namespace Charanis {
	typedef std::map<Ogre::Real, CharacterExpression*> TimedExpressionMap;
} // end of namespace

#endif