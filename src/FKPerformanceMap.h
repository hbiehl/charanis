/*
 *  FKPerformanceMap.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 28.07.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef FK_PERFORMANCE_MAP_H
#define FK_PERFORMANCE_MAP_H

#include "FKPerformanceVector.h"

namespace Charanis {
	typedef std::map<std::string, FKPerformanceVector*> FKPerformanceMap;
} // end of namespace

#endif