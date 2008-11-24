/*
 *  AudioTrack.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 03.09.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "AudioTrack.h"

#include <OpenAL/alc.h>
#include <OpenAL/al.h>

namespace Charanis {

AudioTrack::AudioTrack(std::string filename, Ogre::Real startTime) :
startTime(startTime) {
	int error;
	
	// clear Error
	alGetError();
	
	std::cout << "Creating the buffers" << std::endl;	
	// Create the buffers
	alGenBuffers(1, buffers);
	if ((error = alGetError()) != AL_NO_ERROR) {
		std::cout << "alGenBuffers : " << error << std::endl;
		exit(0);
	}
	
	
	std::cout << "Loading the sound..." << std::endl;
	ALenum     format;
	ALsizei    size;
	ALsizei    freq;
	//ALboolean  loop;
	ALvoid*    data;

/* ****Problem mit XCode-Update **/
	ALbyte* file = (ALbyte*) filename.c_str();
	alutLoadWAVFile(file, &format, &data, &size, &freq);//, &loop);
	//loadWAVFile(file, &format, &data, &size, &freq);//, &loop);
	if ((error = alGetError()) != AL_NO_ERROR) {
		std::cout << "alutLoadWAVFile : " << error << std::endl;
		// Delete Buffers
		alDeleteBuffers(1, buffers);
		exit(0);
	}
	
	
	std::cout << "Filling Buffer..." << std::endl;
	alBufferData(buffers[0],format,data,size,freq);
	if ((error = alGetError()) != AL_NO_ERROR) {
		std::cout << "alBufferData buffer 0 : " << error << std::endl;
		// Delete buffers
		alDeleteBuffers(1, buffers);
		exit(0);
	}
	
	
	std::cout << "Freeing Audio-File..." << std::endl;
	alutUnloadWAV(format,data,size,freq);
	//unloadWAV(format,data,size,freq);
	if ((error = alGetError()) != AL_NO_ERROR) {
		std::cout << "alutUnloadWAV : " << error << std::endl;
		// Delete buffers
		alDeleteBuffers(1, buffers);
		exit(0);
	}
	/** ENDE VOM PROBLEM!*/
}


AudioTrack::~AudioTrack() {
	std::cout << "Freeing the buffers" << std::endl;
	if (alIsBuffer(buffers[0])) {
		std::cout << "IS BUFFER" << std::endl;
	} else {
		std::cout << "IS NOT A VALID BUFFER" << std::endl;
	}
	
	alGetError();
	alDeleteBuffers(1, buffers);
	std::cout << "AudioTrack::AudioTrack()    -   alDeleteBuffers(NUM_BUFFERS, buffers);" << alGetError() << std::endl;
}
		
Ogre::Real AudioTrack::getStartTime() {
	return startTime;
}
		
ALuint AudioTrack::getBuffer() {
	return buffers[0];
}


} //End of Namespace