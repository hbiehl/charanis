/*
 *  main.cpp
 *  Chararnis
 *
 *  Created by Holger Biehl on 29.11.05.
 *  Copyright 2005 __MyCompanyName__. All rights reserved.
 *
 */

//#include <iostream>
//#include <string>
//#include <deque>
//#include <cmath>
//
#include "SDL/SDL.h"
//#include "SDL/SDL_thread.h"
//
//#include "Ogre/Ogre.h" 
//#include "Ogre/OgreFrameListener.h" 
//#include "Ogre/OgreEventListeners.h" 
//#include "Ogre/OgreKeyEvent.h" 


//#include "FEMLParser.h"

//#include <OSTypes>

//#include <libkern/OSTypes.h>
/*
#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <cstddef>

#include <machine/types.h>

extern "C" {
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <sys/cdefs.h>
}*/
/*
typedef unsigned short Uint8;
typedef unsigned int Uint16;
typedef unsigned long Uint32;
typedef unsigned long Uint64;
*/
#include "EngineManager.h"


//using namespace Ogre; 





#ifdef __cplusplus
extern "C"
{
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32 
#define WIN32_LEAN_AND_MEAN 
#include "windows.h" 
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT) 
#else 
int main(int argc, char **argv) 
#endif
{

	//FEMLParser parser = FEMLParser("../../");
	//parser.parseFile("test.feml");



	Charanis::EngineManager em = Charanis::EngineManager();
	return 0;
}
#ifdef __cplusplus
}
#endif
