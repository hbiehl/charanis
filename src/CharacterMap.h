/*
 *  CharacterMap.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 09.02.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#include <string>
#include "Character.h"

#ifndef CHARACTER_MAP_H
#define CHARACTER_MAP_H

namespace Charanis {

typedef std::map<std::string, Character*> CharacterMap;

} // end of namespace

#endif