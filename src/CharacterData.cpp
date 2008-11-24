/*
 *  CharacterData.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 07.04.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#include "CharacterData.h"
// project includes
#include "IntensityInterpolator.h"


namespace Charanis {

CharacterData::CharacterData() {
	boost::mutex::scoped_lock lock(characterDataMutex);
	for (int i=0; i<EMOTION_END; i++) {
		emotionMap[EmotionType(i)] = new IntensityInterpolator(0);
	}
}



CharacterData::~CharacterData() {
	boost::mutex::scoped_lock lock(characterDataMutex);
	for (int i=0; i<EMOTION_END; i++) {
		delete emotionMap[EmotionType(i)];
	}
	emotionMap.clear();
}



void CharacterData::setEmotion(EmotionType type, Ogre::Real time, Ogre::Real value) {
	boost::mutex::scoped_lock lock(characterDataMutex);
	if (emotionMap.find(type) != emotionMap.end()) {
		emotionMap[type]->setIntensity(time, value);
	} else {
		// TODO: throw Exception 
	}
}


Ogre::Real CharacterData::getEmotion(EmotionType type, Ogre::Real time) {
	boost::mutex::scoped_lock lock(characterDataMutex);
	if (emotionMap.find(type) != emotionMap.end()) {
		return emotionMap[type]->getIntensity(time);
	} else {
		// TODO: throw Exception 
	}
}

} // end of namespace