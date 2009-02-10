/*
 *  TimedExpressionMap.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 21.05.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef TIMED_EXPRESSION_MAP_H
#define TIMED_EXPRESSION_MAP_H

// std includes
#include <map>
#include <string>

// dependency includes
#ifdef OSX
    #include <Ogre/OgrePrerequisites.h>
#else
    #include <OgrePrerequisites.h>
#endif

namespace Charanis {
	class CharacterExpression;

	//typedef std::map<Ogre::Real, CharacterExpression*> TimedExpressionMap;
	class TimedExpressionMap : public std::map<Ogre::Real, CharacterExpression*> {
		public:
			void getCurrentExpressions(TimedExpressionMap::iterator& it1, TimedExpressionMap::iterator& it2, Ogre::Real engineTime) {
				it1 = begin();
				it2 = begin();
				
				// gehe bis zum ersten Zeitpunkt größer als der aktuellen Zeit
				while (it2 != end()) {
					if (it2->first > engineTime) {
						break;
					} else {
						it1 = it2;
					}
					
					it2++;
				}
			}
	};
} // end of namespace

#endif
