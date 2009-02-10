/*
 *  ActionScript.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 26.05.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "ActionScript.h"

namespace Charanis {

ActionScript::ActionScript(std::string name) {
	this->name = name;
}

ActionScript::~ActionScript() {
	// ???? nothing to do?
}
		
std::string ActionScript::getName() {
	return name;
}
		
void ActionScript::addExpression(CharacterExpression* expression) {
	expressions.push_back(expression);
}


void ActionScript::addPerformance(CharacterPerformance* performance) {
	performances.push_back(performance);
}

} // end of namespace
