/*
 *  ObserverKeyFrame.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 02.10.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef OBSERVER_KEY_FRAME_H
#define OBSERVER_KEY_FRAME_H

#ifdef OSX
	#include <Ogre/Ogre.h>
#else
	#include <Ogre.h>
#endif

namespace Charanis {

class ObserverKeyFrame {
	private:
		Ogre::Real time;
		Ogre::Vector3 position;
		Ogre::Quaternion orientation;
		Ogre::Vector3 direction;
		//Ogre::Vector3 up;
	
		//Ogre::Radian roll;
		//Ogre::Radian pitch;
		//Ogre::Radian yaw;
	
	public:
		ObserverKeyFrame(Ogre::Real time, Ogre::Vector3 position, Ogre::Vector3 direction); //, Ogre::Vector3 up, Ogre::Quaternion orientation);
		~ObserverKeyFrame();
		
		Ogre::Real getTime();
		void setTime(Ogre::Real time);
		
		Ogre::Vector3 getPosition();
		void setPosition(Ogre::Vector3 position);
		
		Ogre::Vector3 getDirection();
		void setDirection(Ogre::Vector3 direction);
		/*
		Ogre::Vector3 getUp();
		void setUp(Ogre::Vector3 up);
		
		Ogre::Quaternion getOrientation();
		void setOrientation(Ogre::Quaternion orientation);
		
		Ogre::Radian getRoll();
		void setRoll(Ogre::Radian roll);
		
		Ogre::Radian getPitch();
		void setPitch(Ogre::Radian pitch);
		
		Ogre::Radian getYaw();
		void setYaw(Ogre::Radian yaw);
		*/
};

} // end of namespace

#endif
