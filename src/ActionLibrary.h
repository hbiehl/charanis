/*
 *  ActionLibrary.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 28.05.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef ACTION_LIBRARY_H
#define ACTION_LIBRARY_H

// std includes
#include <iostream>
#include <string>

// project includes
#include "ActionScriptMap.h"

namespace Charanis {

class ActionLibrary {
	private:
		std::string characterName;
		
		ActionScriptMap actionMap;
	
	public:
		ActionLibrary(std::string characterName);
		~ActionLibrary();
		
		std::string getCharacterName();
		
		
		void addActionScript(ActionScript* action);
		ActionScript* getActionScript(std::string actionName);
		
		void print();
};

} // end of namespace

#endif
