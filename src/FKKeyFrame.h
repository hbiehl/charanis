/*
 *  FKKeyFrame.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 26.07.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef FK_KEY_FRAME_H
#define FK_KEY_FRAME_H

// dependency includes
#include <Ogre/OgrePrerequisites.h>

namespace Ogre {
class Quaternion;
} // end of namespace Ogre

namespace Charanis {

/**
 * \brief Hilfsklasse der FKPerformance.
 *
 * Dies ist eine Hilfsklasse der FKPerformance. Sie repräsentiert die Keyframes der Skelett-Animation.
 */
class FKKeyFrame {
	private:
		Ogre::Real time;
		Ogre::Quaternion* rotation;
		
	public:
		FKKeyFrame(Ogre::Real time);
		FKKeyFrame(Ogre::Real time, Ogre::Quaternion* rotation);
		
		Ogre::Quaternion* getRotation();
		void setRotation(Ogre::Quaternion* rotation);
		
		Ogre::Real getTime();
};

} // end of namespace

#endif