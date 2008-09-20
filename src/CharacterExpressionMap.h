/*
 *  CharacterExpressionMap.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 21.05.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef CHARACTER_EXPRESSION_MAP_H
#define CHARACTER_EXPRESSION_MAP_H

#include <map>
#include <string>

#include "TimedExpressionMap.h"

namespace Charanis {
	typedef std::map<std::string, TimedExpressionMap*> CharacterExpressionMap;
} // end of namespace

#endif
