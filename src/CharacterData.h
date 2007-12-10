/*
 *  CharacterData.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 07.04.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef CHARACTER_DATA_H
#define CHARACTER_DATA_H

#include <map>

#include <boost/thread/thread.hpp>


#include "IntensityInterpolator.h"
#include "EmotionTypes.h"

namespace Charanis {
			
	
/**
 * \brief Verwaltung von Charakter-Eigenschaften wie Emotionen.
 *
 * Für jeden Charakter der Szene hält der DataManager eine Instanz dieser Klasse im Speicher.
 * Hier werden Eigenschaften der Charaktere verwaltet. In erster Linie sind dies die Emotionen --- künftig könnten das aber
 * auch Charaktereigenschaften sein, die beispielsweise die Persönlichkeit genauer beschreiben und als Parameter für
 * die Animationserzeugung dienen können.
 */
 
class CharacterData {
	public:
		CharacterData();
		~CharacterData();

		void setEmotion(EmotionType type, Ogre::Real time, Ogre::Real value);
		Ogre::Real getEmotion(EmotionType type, Ogre::Real time);
	
			
	private:
		typedef std::map<EmotionType, IntensityInterpolator*> EmotionMap;
		EmotionMap emotionMap;
		
		boost::mutex characterDataMutex;
};

} // end of namespace

#endif