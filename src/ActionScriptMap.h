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

// std includes
#include <map>
#include <string>

namespace Charanis {
	class ActionScript;
	
	typedef std::map<std::string, ActionScript*> ActionScriptMap;
} // end of namespace

#endif