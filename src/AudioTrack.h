/*
 *  AudioTrack.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 03.09.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef AUDIO_TRACK_H
#define AUDIO_TRACK_H

#include "SDL/SDL.h"
#include "Ogre/Ogre.h"

#include "OpenAL/alc.h"
#include "OpenAL/al.h"
#include "alut.h"

namespace Charanis {

	/**
	 * \brief Repräsentiert einen Abspiel-Befehl für eine Audiodatei.
	 *
	 * Diese Klasse repräsentiert einen Abspielbefehl für eine Audiodatei und wird beispielsweise von der Character -Klasse für die Sprachausgabe verwendet.
	 *
	 **/
	class AudioTrack {
		private:
			Ogre::Real startTime;
			
			ALuint buffers[1];
			
		public:
			AudioTrack(std::string filename, Ogre::Real startTime);
			~AudioTrack();
			
			Ogre::Real getStartTime();
			
			ALuint getBuffer();
	};
}

#endif