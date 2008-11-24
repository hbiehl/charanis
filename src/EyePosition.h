/*
 *  EyePosition.h
 *  Charanis
 *
 *  Created by Holger Biehl on 20.11.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef EYE_POSITION_H
#define EYE_POSITION_H

// dependency includes
#include <Ogre/OgrePrerequisites.h>

namespace Charanis {

/**
 * \brief Repräsentation einer Augenposition (UNUSED).
 *
 * DIESE KLASSE WIRD AKTUELL NOCH NICHT VERWENDET!
 */
class EyePosition {
	private:
		Ogre::Real time;
		Ogre::Real leftRight;
		Ogre::Real upDown;
	
	public:
		EyePosition(Ogre::Real time, Ogre::Real leftRight, Ogre::Real upDown);
		
		Ogre::Real getTime();
		void setTime(Ogre::Real time);
		
		Ogre::Real getLeftRight();
		void setLeftRight(Ogre::Real leftRight);
		
		Ogre::Real getUpDown();
		void setUpdDown(Ogre::Real upDown);
};

} // end of namespace

#endif