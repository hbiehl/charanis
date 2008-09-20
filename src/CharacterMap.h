/*
 *  CharacterMap.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 09.02.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef CHARACTER_MAP_H
#define CHARACTER_MAP_H

// std includes
#include <map>
#include <string>

namespace Charanis {
class Character;
typedef std::map<std::string, Character*> CharacterMap;
} // end of namespace

#endif
