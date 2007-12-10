/*
 *  ActionScriptMap.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 28.05.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef ACTION_SCRIPT_MAP_H
#define ACTION_SCRIPT_MAP_H

#include <map>
#include <string>

#include "ActionScript.h"

namespace Charanis {
	typedef std::map<std::string, ActionScript*> ActionScriptMap;
} // end of namespace

#endif