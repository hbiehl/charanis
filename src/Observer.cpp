/*
 *  Observer.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 02.09.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#include "Observer.h"

// dependency includes
#include <Ogre/OgreCamera.h>
#include <Ogre/OgreMath.h>
#include <Ogre/OgreQuaternion.h>
#include <Ogre/OgreRoot.h>
#include <Ogre/OgreSceneManager.h>
#include <Ogre/OgreVector3.h>
#include <OpenAL/al.h>
//#include <OpenAL/alc.h>
// project inludes
#include "DataManager.h"
#include "ObserverKeyFrame.h"

namespace Charanis {

Observer::Observer(DataManager* dataManager, Ogre::Root* root, Ogre::SceneManager* sceneManager) {
	this->dataManager = dataManager;
	this->root = root;
	this->sceneManager = sceneManager;
	
	cameraName = "SimpleCamera";

	
	camera = sceneManager->createCamera(cameraName); 
	camera->setNearClipDistance(5);
	
	root->getAutoCreatedWindow()->addViewport(camera);
	
	
	setPosition(Ogre::Vector3(0, 100, 240));
	
	//addKeyFrame(new ObserverKeyFrame(0, Ogre::Vector3(-40, 0, 140), /*Ogre::Vector3(0, 1, 0), Ogre::Vector3(0, 0, -1));*/Ogre::Quaternion()));
	//addKeyFrame(new ObserverKeyFrame(6, Ogre::Vector3(40, 20, 140), /*Ogre::Vector3(1, 1, 0), Ogre::Vector3(0, 0, -1));*/Ogre::Quaternion(0.8, 1, 0, 0)));
	//addKeyFrame(new ObserverKeyFrame(10, Ogre::Vector3(100, 5, 140), /*Ogre::Vector3(0, 1, 0), Ogre::Vector3(0, 0, -1));*/Ogre::Quaternion(0.1, 1, 1, 0)));
	//addKeyFrame(new ObserverKeyFrame(20, Ogre::Vector3(0, 0, 240), /*Ogre::Vector3(0, 1, 0), Ogre::Vector3(0, 0, -1));*/Ogre::Quaternion()));
	
	
	
	addKeyFrame(new ObserverKeyFrame(0, Ogre::Vector3(-40, 0, 140), Ogre::Vector3(0, 0, -1)));
	addKeyFrame(new ObserverKeyFrame(6, Ogre::Vector3(40, 20, 140), Ogre::Vector3(0, -0.4, -1)));
	addKeyFrame(new ObserverKeyFrame(10, Ogre::Vector3(100, 5, 140), Ogre::Vector3(0, 0, -1)));
	addKeyFrame(new ObserverKeyFrame(20, Ogre::Vector3(0, 0, 240), Ogre::Vector3(-0.1, -0.2, -1)));
}



Observer::~Observer() {
	
}
		

void Observer::setPosition(const Ogre::Vector3 &pos) {
	camera->setPosition(pos);
	updateListener();
}
/*
void Observer::setUp(const Ogre::Vector3 &up) {
	//camera->setUp(up);
	updateListener();
}
*/

void Observer::setDirection(const Ogre::Vector3 &dir) {
	std::cout << "NEW CAMERA DIRECTION=" << dir << std::endl;
	camera->setDirection(dir);
	updateListener();
}

void Observer::setOrientation(const Ogre::Quaternion &quat) {
	camera->setOrientation(quat);
	updateListener();
}


void Observer::moveRelative(const Ogre::Vector3 &vec) {
	camera->moveRelative(vec);
	updateListener();
}


void Observer::roll(const Ogre::Radian &angle) {
	camera->roll(angle);
	updateListener();
}

void Observer::yaw(const Ogre::Radian &angle) {
	camera->yaw(angle);
	updateListener();
}


void Observer::pitch(const Ogre::Radian &angle) {
	camera->pitch(angle);
	updateListener();
}


void Observer::updateListener() {
	Ogre::Vector3 pos = camera->getPosition();
	float vec[3];
	vec[0] = pos.x;
	vec[1] = pos.y;
	vec[2] = pos.z;
	alListenerfv(AL_POSITION, vec); // Problem mit XCode-Update

	float orientation[6];
	Ogre::Vector3 dir = camera->getDirection();
	Ogre::Vector3 up = camera->getUp();
	orientation[0] = dir.x;
	orientation[1] = dir.y;
	orientation[2] = dir.z;
	orientation[3] = up.x;
	orientation[4] = up.y;
	orientation[5] = up.z;
	alListenerfv(AL_ORIENTATION, orientation); // Problem mit XCode-Update
}


void Observer::addKeyFrame(ObserverKeyFrame* kf) {
	keyFrameMap[kf->getTime()] = kf;
}


void Observer::calcCurrentPosition() {
	Ogre::Real engineTime = dataManager->getEngineTime();
	
	
	Ogre::Real t0=0;
	Ogre::Real t1=0;
	// gehe bis zum ersten Zeitpunkt größer als der aktuellen Zeit
	std::map<Ogre::Real, ObserverKeyFrame*>::iterator it = keyFrameMap.begin();
	while (it!=keyFrameMap.end()) {
		if (it->first > engineTime) {
			t1 = it->first;
			break;
		} else {
			t0 = it->first;
		}
		
		it++;
	}
	
	if (t1==0) {
		t1=t0;
	}
	
	// Veraltete KeyFrames löschen
	while ((t0>0) && (keyFrameMap.begin()->first < t0)) {
		ObserverKeyFrame* kf = keyFrameMap.begin()->second;
		keyFrameMap.erase(keyFrameMap.begin()); 
		delete kf;
	}
	
	if (t1==t0) {
		setPosition(keyFrameMap[t0]->getPosition());
	} else {
		Ogre::Real delta = (engineTime-t0) / (t1-t0);
		
		Ogre::Vector3 pos0 = keyFrameMap[t0]->getPosition();
		Ogre::Vector3 pos1 = keyFrameMap[t1]->getPosition();
		
		Ogre::Vector3 deltaPos =  delta * (pos1 - pos0);
		setPosition(pos0 + deltaPos);
		
		
		Ogre::Vector3 dir0 = keyFrameMap[t0]->getDirection();
		Ogre::Vector3 dir1 = keyFrameMap[t1]->getDirection();
		//Ogre::Quaternion q = dir0.getRotationTo(dir1);
		//Ogre::Radian angle;
		//Ogre::Vector3 axis;
		//q.ToAngleAxis(angle, axis);
		
		//setDirection(............);
		
		//Ogre::Quaternion q0 = keyFrameMap[t0]->getOrientation();
		//Ogre::Quaternion q1 = keyFrameMap[t1]->getOrientation();
		//setOrientation(Ogre::Quaternion::Slerp(delta, q0, q1, true));
	}
}

} // end of namespace
