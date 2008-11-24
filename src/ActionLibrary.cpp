/*
 *  ActionLibrary.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 28.05.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "ActionLibrary.h"

// project includes
#include "ActionScript.h"

namespace Charanis {

ActionLibrary::ActionLibrary(std::string characterName) {
	this->characterName = characterName;
}

ActionLibrary::~ActionLibrary() {
	for (ActionScriptMap::iterator it = actionMap.begin(); it!=actionMap.end(); it++) {
		delete it->second;
	}
	actionMap.clear();
}
		
std::string ActionLibrary::getCharacterName() {
	return characterName;
}
		
		
void ActionLibrary::addActionScript(ActionScript* action) {
	actionMap[action->getName()] = action;
}

ActionScript* ActionLibrary::getActionScript(std::string actionName) {
	if (actionMap.find(actionName)==actionMap.end()) {
		return NULL;
	} else {
		return actionMap[actionName];
	}
}


void ActionLibrary::print() {
	std::cout << "(((((((((((((((((((((( ActionLibrary of character " << characterName << " ))))))))))))))))))))))"<< std::endl;
	for (ActionScriptMap::iterator it = actionMap.begin(); it!=actionMap.end(); it++) {
		std::cout << "   - " << it->first << std::endl;
	}
}

} // end of namespace