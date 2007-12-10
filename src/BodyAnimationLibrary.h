/*
 *  BodyAnimationLibrary.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 28.05.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef ANIMATION_LIBRARY_H
#define ANIMATION_LIBRARY_H


#include <map>
#include <string>
#include <iostream>

#include "BodyAnimationMap.h"
#include "SAMLParser.h"


namespace Charanis {

class BodyAnimationLibrary {
	private:
		std::string characterName;
	
		BodyAnimationMap animationMap; // key: name of animation;   value: BodyAnimation
	
	public:
		BodyAnimationLibrary(std::string characterName);
		~BodyAnimationLibrary();
	
		//void importSAMLFile(std::string samlDir, std::string fileName);

		std::string getCharacterName();
		
		void addBodyAnimation(BodyAnimation* anim);
		BodyAnimation* getBodyAnimation(std::string animName);
		
		void print();
};

} // end of namespace

#endif