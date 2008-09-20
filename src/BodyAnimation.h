/*
 *  BodyAnimation.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 28.05.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef BODY_ANIMATION_H
#define BODY_ANIMATION_H

// std includes
#include <string>

namespace Charanis {

class BodyAnimation {
	private:
		std::string name;
	
	public:
		BodyAnimation(std::string name);
		~BodyAnimation();
		
		std::string getName();
};

} // end of namespace

#endif
