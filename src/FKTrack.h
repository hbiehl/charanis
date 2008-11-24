/*
 *  FKTrack.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 26.07.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef FK_TRACK_H
#define FK_TRACK_H

// std includes
#include <string>
// project includes
#include "FKKeyFrameMap.h"

namespace Charanis {

class FKKeyFrame;

/**
 * \brief Hilfsklasse der FKPerformance.
 *
 * Dies ist eine Hilfsklasse der FKPerformance. Sie verwaltet die FKKeyFrame s zu einem Knochen
 * des Modells.
 */
class FKTrack {
	private:
		std::string boneName;
		
		FKKeyFrameMap* fkKeyFrameMap;
		
	public:
		FKTrack(std::string boneName);
		~FKTrack();
		
		void addKeyFrame(FKKeyFrame* keyFrame);
		FKKeyFrameMap* getKeyFrameMap();
		
		std::string getBoneName();
};

} // end of namespace

#endif