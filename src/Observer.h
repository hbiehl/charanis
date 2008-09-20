/*
 *  Observer.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 02.09.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OBSERVER_H
#define OBSERVER_H

// std includes
#include <string>
// dependeny includes
#include "SDL/SDL.h"
    #include <Ogre/OgrePrerequisites.h>
#else
    #include <OgrePrerequisites.h>
#endif


namespace Ogre {
class Camera;
class Quaternion;
class Radian;
class Root;
class SceneManager;
class Vector3;
} // end of namespace Ogre

namespace Charanis {

class DataManager;
class ObserverKeyFrame;

/**
 * \brief Das Auge und Ohr in der Szene.
 *
 * Diese Klasse kapselt die Kamera von Ogre und bindet die Listener von OpenAL ein. Damit ist sie
 * gleichzeitig Auge und Ohr.
 */
class Observer {
	private:
		DataManager* dataManager;
		Ogre::Root* root;
		Ogre::SceneManager* sceneManager;
		
		std::string cameraName;
		Ogre::Camera* camera;
		
		std::map<Ogre::Real, ObserverKeyFrame*> keyFrameMap; // Key=time, Value=ObserverKeyFrame
		
		void updateListener();
		
	public:
		Observer(DataManager* dataManager, Ogre::Root* root, Ogre::SceneManager* sceneManager);
		~Observer();
		
		void setPosition(const Ogre::Vector3 &pos);
		//void setUp(const Ogre::Vector3 &up);
		void setDirection(const Ogre::Vector3 &dir);
		void setOrientation(const Ogre::Quaternion &quat);
		//void setUp(const Ogre::Vector3 &up);
		
		void moveRelative(const Ogre::Vector3 &vec);
		
		void roll(const Ogre::Radian &angle);
		void yaw(const Ogre::Radian &angle);
		void pitch(const Ogre::Radian &angle);
		
		void addKeyFrame(ObserverKeyFrame* kf);
		
		void calcCurrentPosition();
};

} // end of namespace

#endif
