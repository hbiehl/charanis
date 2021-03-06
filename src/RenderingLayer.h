/*
 *  RenderingLayer.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 11.05.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef RENDERING_LAYER_H
#define RENDERING_LAYER_H

// std includes
// dependeny includes
#ifdef OSX
    #include <Ogre/Ogre.h>
    #include <Ogre/OgreFrameListener.h>
#else
    #include <Ogre.h>
    #include <OgreFrameListener.h>
#endif
#include "OIS.h" // TODO: use framework!
// project includes
#include "CharacterMap.h"
#include "PipelineLayer.h"



namespace Charanis {

class Character;
class CharanisInfoPanel;
class EngineManager;
class Observer;

/**
 * \brief Die Hauptklasse der Ausgabeschicht.
 *
 * Der RenderingLayer ist die Hauptklasse der Ausgabeschicht. Als solche �bernimmt er mit
 * seinen Hilfsklassen die Ansteuerung von Ogre und von OpenAL.
 *
 * Der RenderingLayer hat eine eingehende Nachrichten-Warteschlange (PackageQueue), welche von s�mtlichen Charakter-Pipelines,
 * dem NetworkLayer und dem EngineManager gef�llt wird. F�r jeden Charakter h�lt der RenderingLayer ein Character -Objekt im Speicher.
 * Dieses beinhaltet die Bewegungsanweisungen f�r die n�here Zukunft. Weiterhin wird die Kamera durch die Klasse Observer gekapselt
 * und vom RenderingLayer verwaltet. Schlie�lich ist diese Klasse auch noch f�r die Verwaltung der Objekten in der Szene
 * und der Lichtquellen zust�ndig.
 */

class RenderingLayer 
		: public Ogre::FrameListener, public OIS::KeyListener, public OIS::MouseListener, public PipelineLayer {
	private:
		Ogre::RenderWindow* renderWindow;
		EngineManager* engineManager;
		
		OIS::InputManager *inputManager;
		OIS::Mouse *mouse;
		OIS::Keyboard *keyboard;
		
		Observer* observer;
		
		DataManager* dataManager;
		
		Ogre::Real time;
		
		
		Ogre::Root* root;
		Ogre::SceneManager* sceneManager;
	
		CharacterMap* characterMap;
		
		Ogre::Entity *facialEntity;
		
		CharanisInfoPanel* infoPanel;

		
		Ogre::Radian cameraRotX, cameraRotY;
		const Ogre::Real MOUSE_SPEED;
		
		
		
		
		void setAmbientLight(Ogre::ColourValue* color);
		void addDirectionalLight(std::string lightName, Ogre::ColourValue* diffuseColour, Ogre::ColourValue* specularColour, Ogre::Vector3* direction);
		void updateDirectionalLight(std::string lightName, Ogre::ColourValue* diffuseColour, Ogre::ColourValue* specularColour, Ogre::Vector3* direction);
		void removeDirectionalLight(std::string lightName);
	public:
		RenderingLayer(EngineManager* em, DataManager* dm, const std::string &pluginFileName, const std::string &configFileName, const std::string &logFileName);
		~RenderingLayer();
	
	
	
		void loadResources(const std::string &resourcesFileName);
		void initialize(); 
		
		void setupScene();
		
		
		Ogre::Entity* getFacialEntity() { return facialEntity; }
		
		Ogre::Root* getOgreRoot() { return root; }
		Ogre::SceneManager* getSceneManager();
		
		Character* getCharacter(std::string characterName);
		Character* addCharacter(std::string characterName, std::string mesh, Ogre::Vector3* position, Ogre::Vector3* direction, Ogre::Real scale=1);
		bool removeCharacter(std::string characterName);
		CharacterMap* getCharacterMap();
		
		bool addObject(const std::string &objectName, const std::string &mesh, Ogre::Vector3* position, Ogre::Quaternion* orientation, Ogre::Real scale=1);
		bool removeObject(std::string objectName);
		
		void updateTimeStats(long time);
		void updateCharacterStats();
	
		void run();
	
		bool frameStarted(const Ogre::FrameEvent& evt);
		bool frameEnded(const Ogre::FrameEvent& evt);
		

		bool processUnbufferedMouseInput(const Ogre::FrameEvent& evt);

		bool keyPressed(const OIS::KeyEvent &evt);
		bool keyReleased(const OIS::KeyEvent &evt);
		
		// MouseListener
		bool mouseMoved(const OIS::MouseEvent &evt);
		bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID);
		bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID);
	
};

} // end of namespace

#endif
