/*
 *  IntensityInterpolator.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 27.01.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef INTENSITY_INTERPOLATOR_H
#define INTENSITY_INTERPOLATOR_H


#include <cmath>
#include <map>


#include "Ogre/Ogre.h"
#include "InvalidTimingException.h"


namespace Charanis {

typedef std::map<Ogre::Real, Ogre::Real> IntensityMap;

class IntensityInterpolator {
	private:
		//Ogre::Real length;
		
		// key=time; value=intensity
		IntensityMap intensityMap;
			
	public:
		typedef std::map<Ogre::Real, Ogre::Real>::iterator IntensityIterator;

		//IntensityInterpolator(Ogre::Real len, Ogre::Real initialIntensity);
		IntensityInterpolator(Ogre::Real initialIntensity);
		
		//Ogre::Real getLength();
		
		void setIntensity(Ogre::Real time, Ogre::Real intensity);
		Ogre::Real getIntensity(Ogre::Real time);
		
		IntensityMap* getIntensityMap();
};

} // end of namespace

#endif