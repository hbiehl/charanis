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

#include "SDL/SDL.h"
#include "Ogre/Ogre.h"
#include "Ogre/OgreFrameListener.h"
#include "Ogre/OgreEventListeners.h" 
#include "Ogre/OgreKeyEvent.h"
#include "Ogre/OgreStringConverter.h"
#include "Ogre/OgreTextAreaOverlayElement.h"


#include "CharacterMap.h"
#include "Character.h"
#include "FacialExpression.h"

#include "PipelineLayer.h"
#include "CharacterDataPackage.h"
#include "CharacterSoundPackage.h"
#include "AddCharacterPackage.h"
#include "RemoveCharacterPackage.h"
#include "ImportFEMLFilePackage.h"
#include "ImportSAMLFilePackage.h"
#include "CameraControlPackage.h"
#include "AddObjectPackage.h"
#include "RemoveObjectPackage.h"
#include "AmbientLightPackage.h"
#include "DirectionalLightPackage.h"
#include "RemoveDirectionalLightPackage.h"

#include "Observer.h"

namespace Charanis {

class EngineManager;


/**
 * \brief Die Hauptklasse der Ausgabeschicht.
 *
 * Der RenderingLayer ist die Hauptklasse der Ausgabeschicht. Als solche übernimmt er mit
 * seinen Hilfsklassen die Ansteuerung von Ogre und von OpenAL.
 *
 * Der RenderingLayer hat eine eingehende Nachrichten-Warteschlange (PackageQueue), welche von sämtlichen Charakter-Pipelines,
 * dem NetworkLayer und dem EngineManager gefüllt wird. Für jeden Charakter hält der RenderingLayer ein Character -Objekt im Speicher.
 * Dieses beinhaltet die Bewegungsanweisungen für die nähere Zukunft. Weiterhin wird die Kamera durch die Klasse Observer gekapselt
 * und vom RenderingLayer verwaltet. Schließlich ist diese Klasse auch noch für die Verwaltung der Objekten in der Szene
 * und der Lichtquellen zuständig.
 */

class RenderingLayer 
		: public Ogre::FrameListener, public Ogre::KeyListener, public Ogre::MouseMotionListener, public PipelineLayer {
	private:
		Ogre::EventProcessor* eventProcessor;
		Ogre::InputReader* inputReader;
		Ogre::RenderWindow* renderWindow;
		EngineManager* engineManager;
		
		Observer* observer;
		
		DataManager* dataManager;
		
		Ogre::Real time;
		
		
		Ogre::Root* root;
		Ogre::SceneManager* sceneManager;
	
		CharacterMap* characterMap;
		
		Ogre::Entity *facialEntity;
		
		
		Ogre::TextAreaOverlayElement* timeTextArea;
		Ogre::TextAreaOverlayElement* characterTextArea;
		
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
		//void updateListener();
	
		void run();
	
		bool frameStarted(const Ogre::FrameEvent& evt);
		bool frameEnded(const Ogre::FrameEvent& evt);
		
		bool processUnbufferedMouseInput(const Ogre::FrameEvent& evt);
						
		void keyClicked(Ogre::KeyEvent* e);
		void keyPressed(Ogre::KeyEvent* e); 
		void keyReleased(Ogre::KeyEvent* e);
		
		void mouseMoved(Ogre::MouseEvent *e);
		void mouseDragged(Ogre::MouseEvent *e);
		void mouseDragMoved(Ogre::MouseEvent *e);
};

} // end of namespace

#endif