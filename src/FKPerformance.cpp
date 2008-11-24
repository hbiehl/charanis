/*
 *  FKPerformance.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 26.07.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#include "FKPerformance.h"
// dependency includes
#include <Ogre/OgreAnimation.h>
#include <Ogre/OgreBone.h>
#include <Ogre/OgreEntity.h>
#include <Ogre/OgreSkeleton.h>
#include <Ogre/OgreSkeletonInstance.h>
// project includes
#include "CharacterPerformance.h"
#include "FKKeyFrame.h"
#include "FKTrack.h"

namespace Charanis {
	

FKPerformance::FKPerformance(std::string animationName, std::string characterName, Ogre::Real length) :
animationName(animationName), characterName(characterName), length(length) {
	//std::cout << "CONSTRUCTOR FK_PERFORMANCE" << std::endl;
	characterPerformance = NULL;
}


FKPerformance::~FKPerformance() {
	for (FKTrackMap::iterator it=fkTrackMap.begin(); it!=fkTrackMap.end(); it++) {
		delete it->second;
	}
	fkTrackMap.clear();
}


void FKPerformance::addTrack(FKTrack* track) {
	fkTrackMap[track->getBoneName()] = track;
}
	

std::string FKPerformance::getAnimationName() {
	return animationName;
}


std::string FKPerformance::getCharacterName() {
	return characterName;
}

void FKPerformance::setLength(Ogre::Real length) {
	this->length = length;
}

Ogre::Real FKPerformance::getLength() {
	return length;
}



void FKPerformance::setCharacterPerformance(CharacterPerformance* characterPerformance) {
	this->characterPerformance = characterPerformance;
}


CharacterPerformance* FKPerformance::getCharacterPerformance() {
	return characterPerformance;
}
		
		

Ogre::Animation* FKPerformance::createOgreAnimation(Ogre::Entity* entity) {
	//std::cout << "FKPerformance::createOgreAnimation() /"<< animationName <<"/ BEGIN" << std::endl;
	Ogre::Skeleton* skel = entity->getSkeleton();
	
	Ogre::Animation* ogreAnim = skel->createAnimation(animationName, length);
	
	FKTrackMap::iterator it;
	for (it=fkTrackMap.begin(); it!=fkTrackMap.end(); it++) {
		std::string boneName = (std::string) it->first;
		
		Ogre::Bone* bone = NULL;
		try {
			bone = skel->getBone(boneName);
		} catch (...) {
			std::cout << "======================  KFPerformance-Error ======================" << std::endl;
			std::cout << "Das Modell vom Charakter " << characterName << " hat keinen Knochen namens " << boneName << " in dem Skelett." << std::endl;
			std::cout << "Der entsprechende Track wird ignoriert." << std::endl;
			std::cout << "==================================================================" << std::endl;
			continue;
		}
		
		
		
		if (bone != NULL) {
			FKTrack* fkTrack = (FKTrack*) it->second;
			Ogre::NodeAnimationTrack* ogreTrack = ogreAnim->createNodeTrack(bone->getHandle(), bone);
			FKKeyFrameMap* kfMap = fkTrack->getKeyFrameMap();
			for (FKKeyFrameMap::iterator kfIt = kfMap->begin(); kfIt!=kfMap->end(); kfIt++) {
				Ogre::Real time = (Ogre::Real) kfIt->first;
				FKKeyFrame* keyFrame = (FKKeyFrame*) kfIt->second;
				
				Ogre::TransformKeyFrame* ogreKf = ogreTrack->createNodeKeyFrame(time);
				ogreKf->setRotation(*(keyFrame->getRotation()));
			}
		}
	}
	//std::cout << "FKPerformance::createOgreAnimation() /"<< animationName <<"/ END" << std::endl;
	return ogreAnim;
}

} // end of namespace