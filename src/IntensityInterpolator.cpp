/*
 *  IntensityInterpolator.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 27.01.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#include "IntensityInterpolator.h"
// project includes
#include "InvalidTimingException.h"


namespace Charanis {

IntensityInterpolator::IntensityInterpolator( Ogre::Real initialIntensity)  {
	intensityMap[0] = initialIntensity;
}





void IntensityInterpolator::setIntensity(Ogre::Real time, Ogre::Real intensity) {
	intensityMap[time] = intensity;
}





Ogre::Real IntensityInterpolator::getIntensity(Ogre::Real time) {
	std::map<Ogre::Real, Ogre::Real>::reverse_iterator lastElement = intensityMap.rbegin();
	//std::cout << "getIntensity (Time=" << time << "     LastTime=" << lastElement->first << ")" << std::endl;
	
	if(time >= lastElement->first) {
		//std::cout << "FINISHED (" << time << "  of " << lastElement->first << ")" << std::endl;
		// return the last value of the intensityMap
		return lastElement->second;
	} else { 
		// Interpolation needed
		std::map<Ogre::Real, Ogre::Real>::iterator sourceIt = intensityMap.upper_bound(time);
		if (sourceIt!=intensityMap.begin()) {
			sourceIt--;
		}
		
		std::map<Ogre::Real, Ogre::Real>::iterator destIt = intensityMap.upper_bound(time);
		
		
		Ogre::Real intensity;
		
		Ogre::Real sourceTime = sourceIt->first;
		Ogre::Real sourceIntensity = sourceIt->second;
		
		Ogre::Real destTime = destIt->first;
		Ogre::Real destIntensity = destIt->second;
		
		//std::cout << sourceTime << " " << sourceIntensity << "->" << destTime << " " << destIntensity << std::endl;
		
		
		if ((destTime > sourceTime) && (sourceIntensity != destIntensity)) {
			Ogre::Real relativeTime = 1 - (destTime - time) / (destTime - sourceTime);
			intensity = sourceIntensity +  relativeTime * (destIntensity - sourceIntensity);
		} else {
			intensity = destIntensity;
		}
		
		
		return intensity;
	}	
}

	
IntensityMap* IntensityInterpolator::getIntensityMap() {
	IntensityMap* copy = new IntensityMap();
	
	for (IntensityMap::iterator it = intensityMap.begin(); it!=intensityMap.end(); it++) {
		(*copy)[it->first] = it->second;
	}
	
	return copy;
} 

} // end of namespace