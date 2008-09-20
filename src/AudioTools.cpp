/*
 *  AudioTools.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 07.09.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "AudioTools.h"

namespace Charanis {

AudioTools::AudioTools() {}
AudioTools::~AudioTools() {}

std::string AudioTools::getALErrorString(ALenum err) {
	switch(err) {
		case AL_NO_ERROR:
			return std::string("AL_NO_ERROR");
			break;

		case AL_INVALID_NAME:
			return std::string("AL_INVALID_NAME");
			break;

		case AL_INVALID_ENUM:
			return std::string("AL_INVALID_ENUM");
			break;

		case AL_INVALID_VALUE:
			return std::string("AL_INVALID_VALUE");
			break;

		case AL_INVALID_OPERATION:
			return std::string("AL_INVALID_OPERATION");
			break;

		case AL_OUT_OF_MEMORY:
			return std::string("AL_OUT_OF_MEMORY");
			break;
	};
	return "Unknown AL Error";
}



std::string AudioTools::getALCErrorString(ALenum err) {
	switch(err) {
		case ALC_NO_ERROR:
			return std::string("AL_NO_ERROR");
			break;

		case ALC_INVALID_DEVICE:
			return std::string("ALC_INVALID_DEVICE");
			break;

		case ALC_INVALID_CONTEXT:
			return std::string("ALC_INVALID_CONTEXT");
			break;

		case ALC_INVALID_ENUM:
			return std::string("ALC_INVALID_ENUM");
			break;

		case ALC_INVALID_VALUE:
			return std::string("ALC_INVALID_VALUE");
			break;

		case ALC_OUT_OF_MEMORY:
			return std::string("ALC_OUT_OF_MEMORY");
			break;
	};
	return "Unknown ALC Error";
}




ALuint AudioTools::loadALBuffer(std::string path) {
	// Variables to store data which defines the buffer.
	ALenum format;
	ALsizei size;
	ALvoid* data;
	ALsizei freq;
	//ALboolean loop;

	// Buffer id and error checking variable.
	ALuint buffer;
	ALenum result;

	// Generate a buffer. Check that it was created successfully.
	alGenBuffers(1, &buffer);

	if ((result = alGetError()) != AL_NO_ERROR)
		throw getALErrorString(result);

	// Read in the wav data from file. Check that it loaded correctly.
	#ifdef OSX
	alutLoadWAVFile((ALbyte*) path.c_str(), &format, &data, &size, &freq);//, &loop);
	#else	
	alutLoadWAVFile((ALbyte*) path.c_str(), &format, &data, &size, &freq, &loop);
	#endif

	if ((result = alGetError()) != AL_NO_ERROR)
		throw getALErrorString(result);

	// Send the wav data into the buffer. Check that it was received properly.
	alBufferData(buffer, format, data, size, freq);

	if ((result = alGetError()) != AL_NO_ERROR)
		throw getALErrorString(result);

	// Get rid of the temporary data.
	alutUnloadWAV(format, data, size, freq);

	if ((result = alGetError()) != AL_NO_ERROR)
		throw getALErrorString(result);

	// Return the buffer id.
	return buffer;
}




ALuint AudioTools::getLoadedALBuffer(std::string path) {
	int count = 0; // 'count' will be an index to the buffer list.

	ALuint buffer; // Buffer id for the loaded buffer.


	// Iterate through each file path in the list.
	for (std::vector<std::string>::iterator iter = loadedFiles.begin(); iter != loadedFiles.end(); ++iter, count++)
	{
		// If this file path matches one we have loaded already, return the buffer id for it.
		if(*iter == path)
			return buffers[count];
	}

	// If we have made it this far then this file is new and we will create a buffer for it.
	buffer = loadALBuffer(path);

	// Add this new buffer to the list, and register that this file has been loaded already.
	buffers.push_back(buffer);

	loadedFiles.push_back(path);

	return buffer;
}


void AudioTools::loadALSample(ALuint* source, std::string path, bool loop) {
	ALuint buffer;
	ALenum result;

	// Get the files buffer id (load it if necessary).
	buffer = getLoadedALBuffer(path);

	// Generate a source.
	//alGenSources(1 source);

	if ((result = alGetError()) != AL_NO_ERROR)
		throw getALErrorString(result);

	// Setup the source properties.
	alSourcei (*source, AL_BUFFER,   buffer   );
	//alSourcef (*source, AL_PITCH,    1.0      );
	//alSourcef (*source, AL_GAIN,     1.0      );
	//alSourcefv(*source, AL_POSITION, SourcePos);
	//alSourcefv(*source, AL_VELOCITY, SourceVel);
	alSourcei (*source, AL_LOOPING,  loop);
}

} // end of namespace
