/*
 *  FKTrack.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 26.07.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#include "FKTrack.h"
// project includes
#include "FKKeyFrame.h"

namespace Charanis {

FKTrack::FKTrack(std::string boneName) :
boneName(boneName) {
	//std::cout << "CONSTRUCTOR FK_PERFORMANCE - BEGIN" << std::endl;
	fkKeyFrameMap = new FKKeyFrameMap();
	//std::cout << "CONSTRUCTOR FK_PERFORMANCE - END" << std::endl;
}


FKTrack::~FKTrack() {
	for (FKKeyFrameMap::iterator it = fkKeyFrameMap->begin(); it!=fkKeyFrameMap->end(); it++) {
		delete it->second;
	}
	fkKeyFrameMap->clear();
	delete fkKeyFrameMap;
}


void FKTrack::addKeyFrame(FKKeyFrame* keyFrame) {
	(*fkKeyFrameMap)[keyFrame->getTime()] = keyFrame;
}


FKKeyFrameMap* FKTrack::getKeyFrameMap() {
	return fkKeyFrameMap;
}

std::string FKTrack::getBoneName() {
	return boneName;
}

} // end of namespace