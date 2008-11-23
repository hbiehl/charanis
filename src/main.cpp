/*
 *  main.cpp
 *  Chararnis
 *
 *  Created by Holger Biehl on 29.11.05.
 *  Copyright 2005 __MyCompanyName__. All rights reserved.
 *
 */





#include "EngineManager.h"




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
	Charanis::EngineManager em = Charanis::EngineManager();
	return 0;
}
#ifdef __cplusplus
}
#endif
