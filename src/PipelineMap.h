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

// std includes
#include <map>
#include <string>

namespace Charanis {
	class Pipeline;
	typedef std::map<std::string, Pipeline*> PipelineMap;
} // end of namespace

#endif
