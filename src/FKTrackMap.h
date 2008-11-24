/*
 *  FKTrackMap.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 26.07.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef FK_TRACK_MAP_H
#define FK_TRACK_MAP_H

#include <string>

namespace Charanis {

class FKTrack;

typedef std::map<std::string, FKTrack*> FKTrackMap;	
} // end of namespace
#endif