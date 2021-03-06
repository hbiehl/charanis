/*
 *  AudioTools.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 07.09.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef AUDIO_TOOLS_H
#define AUDIO_TOOLS_H

#include <string>
#include <vector>

#ifdef OSX
    #include <OpenAL/alc.h>
    #include "alut.h" // Problem mit XCode-Update
#else
    #include <AL/alc.h>
    #include <AL/alut.h>
#endif


namespace Charanis {


class AudioTools {
	private:
		std::vector<std::string> loadedFiles; // Holds loaded file paths temporarily.
		std::vector<ALuint> buffers; // Holds all loaded buffers.
		std::vector<ALuint> sources; // Holds all validated sources.

	public:
		AudioTools();
		~AudioTools();
		
		std::string getALErrorString(ALenum err);
	
	
	
		std::string getALCErrorString(ALenum err);
		
		
		
		
		ALuint loadALBuffer(std::string path);
		
		
		
		ALuint getLoadedALBuffer(std::string path);
		
		
		void loadALSample(ALuint* source, std::string path, bool loop);
};

} // end of namespace
#endif
