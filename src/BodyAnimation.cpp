/*
 *  BodyAnimation.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 28.05.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "BodyAnimation.h"

namespace Charanis {

BodyAnimation::BodyAnimation(std::string name) {
	this->name = name;
}

BodyAnimation::~BodyAnimation() {}
		
std::string BodyAnimation::getName() {
	return name;
}

} // end of namespace