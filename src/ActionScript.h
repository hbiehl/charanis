/*
 *  ActionScript.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 26.05.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef ACTION_SCRIPT_H
#define ACTION_SCRIPT_H

// std includes
#include <string>
#include <vector>

namespace Charanis {

class CharacterExpression;
class CharacterPerformance;

class ActionScript {
	private:
		std::string name;
	
		std::vector<CharacterExpression*> expressions;
		std::vector<CharacterPerformance*> performances;
		
	public:
		ActionScript(std::string name);
		~ActionScript();
		
		std::string getName();
		
		void addExpression(CharacterExpression* expression);
		void addPerformance(CharacterPerformance* performance);
};

} // end of namespace

#endif
