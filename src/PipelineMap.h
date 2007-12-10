/*
 *  PipelineMap.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 10.08.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef PIPELINE_MAP_H
#define PIPELINE_MAP_H

#include <map>
#include <string>
#include "Pipeline.h"

namespace Charanis {
	typedef std::map<std::string, Pipeline*> PipelineMap;
} // end of namespace

#endif