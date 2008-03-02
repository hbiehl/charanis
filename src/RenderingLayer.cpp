/*
 *  RenderLayer.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 11.05.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "RenderingLayer.h"

#include "EngineManager.h"

namespace Charanis {


RenderingLayer::RenderingLayer(EngineManager* em, DataManager* dm, const std::string &pluginFileName, const std::string &configFileName, const std::string &logFileName) 
: PipelineLayer(dm, "RenderLoop"), MOUSE_SPEED(1.5) {
	std::cout << "==== RenderLoop Konstruktor ====" << std::endl;
	
	
	root = new Ogre::Root(pluginFileName, configFileName, logFileName);
	characterMap = new CharacterMap();
	dataManager = dm;
	engineManager = em,
	
	
	loadResources("../../../../cfg/resources.cfg");
	initialize();
	setupScene();
	root->addFrameListener(this);
	
	
	
	std::cout << "INITIALIZING OIS" << std::endl;
	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	renderWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	inputManager = OIS::InputManager::createInputSystem( pl );

	//Create all devices
	bool bufferedKeys=false;
	bool bufferedMouse=false;
	keyboard = static_cast<OIS::Keyboard*>(inputManager->createInputObject( OIS::OISKeyboard, bufferedKeys ));
	mouse = static_cast<OIS::Mouse*>(inputManager->createInputObject( OIS::OISMouse, bufferedMouse ));
	std::cout << "[DONE]" << std::endl;
	
	
	
	
	time = 0;
	
	std::cout << "==== ENDE      RenderLoop Konstruktor ====" << std::endl;
}



RenderingLayer::~RenderingLayer() {
	std::cout << "===== Destructor of RenderLoop BEGIN =====" << std::endl;


	// Charaktere aufräumen
	CharacterMap::iterator it;
	for (it = characterMap->begin(); it!=characterMap->end(); it++) {
		std::cout << "deleting character " << (*it).first << std::endl;
		delete (*it).second;
	}
	characterMap->clear();


	// OIS aufräumen
	if (inputManager) {
		inputManager->destroyInputObject( mouse );
		inputManager->destroyInputObject( keyboard );

		OIS::InputManager::destroyInputSystem(inputManager);
		inputManager = 0;
	}
	

	
	delete root;
	
	std::cout << "===== Destructor of RenderLoop END =====" << std::endl;
}







void RenderingLayer::loadResources(const std::string &resourcesFileName) {
	Ogre::ConfigFile cf;
	cf.load(resourcesFileName);

	// Go through all sections & settings in the file
	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
		
	std::string secName, typeName, archName;
	while (seci.hasMoreElements())	{
		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin(); i != settings->end(); ++i) {
			typeName = i->first;
			archName = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
				archName, typeName, secName);
		}
	}
}



void RenderingLayer::initialize() { //Ogre::SceneType sceneType) {
	// TODO: sceneType aus Config auslesen
	Ogre::SceneType sceneType = Ogre::ST_GENERIC;
	root->showConfigDialog();
	renderWindow = root->initialise(true, "Simple Ogre App");
	
	sceneManager = root->createSceneManager(sceneType, "GenericSceneManager");
	//sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
	sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_MODULATIVE);
	
	observer = new Observer(dataManager, root, sceneManager);
	
	
	
		
	Ogre::Animation::setDefaultInterpolationMode(Ogre::Animation::IM_LINEAR);
	Ogre::Animation::setDefaultRotationInterpolationMode(Ogre::Animation::RIM_LINEAR);
	
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	
	infoPanel = new CharanisInfoPanel();
	
	//Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(Ogre::TFO_TRILINEAR);
	//Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(1);
	Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(Ogre::TFO_ANISOTROPIC);
	Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(8);
	}


void RenderingLayer::setAmbientLight(Ogre::ColourValue* colour) {
	sceneManager->setAmbientLight(*colour);
}


void RenderingLayer::addDirectionalLight(std::string lightName, Ogre::ColourValue* diffuseColour, Ogre::ColourValue* specularColour, Ogre::Vector3* direction) {
	if (!sceneManager->hasLight(lightName)) {
		Ogre::Light *l = sceneManager->createLight(lightName);
		l->setType(Ogre::Light::LT_DIRECTIONAL);
		l->setDiffuseColour(*diffuseColour);
		l->setSpecularColour(*specularColour);
		l->setDirection(*direction);	
		l->setCastShadows(true);
	}
}

void RenderingLayer::updateDirectionalLight(std::string lightName, Ogre::ColourValue* diffuseColour, Ogre::ColourValue* specularColour, Ogre::Vector3* direction) {
	if (sceneManager->hasLight(lightName)) {
		Ogre::Light *l = sceneManager->getLight(lightName);
		l->setDiffuseColour(*diffuseColour);
		l->setSpecularColour(*specularColour);
		l->setDirection(*direction);	
	}
}


void RenderingLayer::removeDirectionalLight(std::string lightName) {
	if (sceneManager->hasLight(lightName)) {
		sceneManager->destroyLight(lightName);
	}
}


void RenderingLayer::setupScene() {
	// Light - defaul: no light at all
	setAmbientLight(new Ogre::ColourValue(0, 0, 0));

	// Shadow
	sceneManager->setShadowTechnique( Ogre::SHADOWTYPE_STENCIL_ADDITIVE );
	
	// FloorPlane
	Ogre::Plane p;
	p.normal = Ogre::Vector3::UNIT_Y;
	//p.d = 50;
	p.d = 0;
	Ogre::MeshManager::getSingleton().createPlane("FloorPlane",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
		p, 2000, 2000, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);

	// Create an entity (the floor)
	Ogre::Entity *floorEnt = sceneManager->createEntity("floor", "FloorPlane");
	floorEnt->setMaterialName("Examples/Rockwall");
	floorEnt->setCastShadows(false);
	sceneManager->getRootSceneNode()->attachObject(floorEnt);

	// Fog
	//sceneManager->setFog(Ogre::FOG_EXP2);
	
	// Sky
	sceneManager->setSkyDome(true, "Examples/CloudySky", 5, 8);
}






Ogre::SceneManager* RenderingLayer::getSceneManager() {
	return sceneManager;
}




Character* RenderingLayer::getCharacter(std::string characterName) {
	if (characterMap->find(characterName)==characterMap->end()) {
		return NULL;
	} else {
		return (*characterMap)[characterName];
	}
}



Character* RenderingLayer::addCharacter(std::string characterName, std::string mesh, Ogre::Vector3* position, Ogre::Vector3* direction, Ogre::Real scale) {
	if (characterMap->find(characterName)!=characterMap->end()) {
		return NULL;
	} else {
		Character* character = new Character(sceneManager, sceneManager->getRootSceneNode(), mesh, dataManager, characterName, scale);
		character->setPosition(*position);
		character->setDirection(*direction);
		(*characterMap)[characterName] = character;
		updateCharacterStats();
		return character;
	}
}



bool RenderingLayer::removeCharacter(std::string characterName) {
	std::cout << "============================ RENDERING_LAYER::REMOVE_CHARACTER(" << characterName << ")" << std::endl;
	if (characterMap->find(characterName)!=characterMap->end()) {
		delete (*characterMap)[characterName];
		characterMap->erase(characterName);
		updateCharacterStats();
		return true;
	}
	return false;	
}


CharacterMap* RenderingLayer::getCharacterMap() {
	return characterMap;
}



bool RenderingLayer::addObject(const std::string &objectName, const std::string &mesh, Ogre::Vector3* position, Ogre::Quaternion* orientation, Ogre::Real scale) {
	if (sceneManager->hasEntity(objectName)) {
		// An Object with the given name allready exists!
		return false;
	} else {
		Ogre::Entity* entity = sceneManager->createEntity(objectName, mesh);//"FatMan.mesh");
		Ogre::SceneNode* sceneNode = sceneManager->getRootSceneNode()->createChildSceneNode(objectName+"Node");
		sceneNode->attachObject(entity);
		sceneNode->setPosition(*position);
		sceneNode->setOrientation(*orientation);
		sceneNode->setScale(Ogre::Vector3(scale, scale, scale));
		return true;
	}
}


bool RenderingLayer::removeObject(std::string objectName) {
	if (sceneManager->hasEntity(objectName)) {
		Ogre::Entity* entity = sceneManager->getEntity(objectName);
		Ogre::SceneNode* sceneNode = entity->getParentSceneNode();
	
		sceneNode->detachObject(entity);
		sceneManager->destroyEntity(entity->getName());
	
		sceneNode->getParentSceneNode()->removeAndDestroyChild(sceneNode->getName());
		return true;
	} else {
		return false;
	}
}
	





void RenderingLayer::updateCharacterStats() {
	infoPanel->updateCharacterStats(*characterMap);
}


void RenderingLayer::updateTimeStats(long time) {
	infoPanel->updateTimeStats(time);
}



void RenderingLayer::run() {
	root->startRendering();
}


bool RenderingLayer::frameStarted(const Ogre::FrameEvent& evt) {
	//std::cout << "frame started" << std::endl;
	keyboard->capture();
	mouse->capture();
	
	processUnbufferedMouseInput(evt);
	
	long oldTime = (long) time;
	time += evt.timeSinceLastFrame;
	dataManager->setEngineTime(time);
	if (oldTime < (long) time) {
		updateTimeStats((long) time);
	}
	
	
	
	
	while ((getInputQueue() != NULL) && (getInputQueue()->size() > 0)) {	
		//std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$ THERE IS A PACKAGE IN THE QUEUE $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << std::endl;
		Package* pkg = getInputQueue()->getPackage();
		if (pkg != NULL) {
			std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << std::endl;
			std::cout << "$$$$$$$$$$$$$$$$ RenderingLayer has received a package!!! $$$$$$$$$$$$$$$$" << std::endl;
			std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << std::endl;
			if (pkg->getType()==Package::CHARACTER_DATA_PACKAGE_TYPE) {
				CharacterDataPackage* package = (CharacterDataPackage*) pkg;
				
				
				
				CharacterMap* characterMap = getCharacterMap();
				
				std::string characterName = package->getCharacterName();
				if (characterMap->find(characterName) != characterMap->end()) {
					// Alle CharacterPerformances aus dem Datenpaket auslesen und in das Charakter-Objekt schieben
					(*characterMap)[characterName]->addPerformances(package->getAllCharacterPerformances());
					
					// Alle FKPerformances aus dem Datenpaket auslesen und in das Charakter-Objekt schieben
					(*characterMap)[characterName]->addFKPerformances(package->getAllFKPerformances());
					
					// Alle SpeechExpressions aus dem Datenpaket auslesen und in das Charakter-Objekt schieben
					(*characterMap)[characterName]->addSpeechExpressions(package->getAllSpeechExpressions());
					
					// Alle ControlledExpressions aus dem Datenpaket auslesen und in das Charakter-Objekt schieben				
					(*characterMap)[characterName]->addControlledExpressions(package->getAllControlledExpressions());
				}
			} else if (pkg->getType()==Package::ADD_CHARACTER_PACKAGE_TYPE) {
				AddCharacterPackage* package = (AddCharacterPackage*) pkg;
				addCharacter(package->getCharacterName(), package->getMeshName(), package->getPosition(), package->getDirection(), package->getScale());
			} else if (pkg->getType()==Package::REMOVE_CHARACTER_PACKAGE_TYPE) {
				RemoveCharacterPackage* package = (RemoveCharacterPackage*) pkg;
				removeCharacter(package->getCharacterName());
			} else if (pkg->getType()==Package::IMPORT_FEML_FILE_PACKAGE_TYPE) {
				ImportFEMLFilePackage* package = (ImportFEMLFilePackage*) pkg;
				(*characterMap)[package->getCharacterName()]->importFEMLFile(package->getFileName());
			} else if (pkg->getType()==Package::IMPORT_SAML_FILE_PACKAGE_TYPE) {
				ImportSAMLFilePackage* package = (ImportSAMLFilePackage*) pkg;
				(*characterMap)[package->getCharacterName()]->importSAMLFile(package->getFileName());
			} else if (pkg->getType()==Package::CHARACTER_SOUND_PACKAGE_TYPE) {
				CharacterSoundPackage* package = (CharacterSoundPackage*) pkg;
				std::string path = dataManager->getConfig()->getSoundDirectory();//"../../";
				getCharacter(package->getCharacterName())->addAudioTrack(new AudioTrack(path+package->getFileName(), package->getStartTime()));
			} else if (pkg->getType()==Package::ADD_OBJECT_PACKAGE_TYPE) {
				AddObjectPackage* package = (AddObjectPackage*) pkg;
				addObject(package->getObjectName(), package->getMeshName(), package->getPosition(), package->getOrientation(), package->getScale());
			} else if (pkg->getType()==Package::REMOVE_OBJECT_PACKAGE_TYPE) {
				RemoveObjectPackage* package = (RemoveObjectPackage*) pkg;
				removeObject(package->getObjectName());
			} else if (pkg->getType()==Package::CAMERA_CONTROL_PACKAGE_TYPE) {
				CameraControlPackage* package = (CameraControlPackage*) pkg;
				observer->setPosition(*package->getPosition());
				observer->setDirection(*package->getDirection());
			} else if (pkg->getType()==Package::AMBIENT_LIGHT_PACKAGE_TYPE) {
				AmbientLightPackage* package = (AmbientLightPackage*) pkg;
				setAmbientLight(package->getAmbientColour());
			} else if (pkg->getType()==Package::DIRECTIONAL_LIGHT_PACKAGE_TYPE) {
				DirectionalLightPackage* package = (DirectionalLightPackage*) pkg;
				std::string lightName = package->getLightName();
				if (sceneManager->hasLight(lightName)) {
					updateDirectionalLight(lightName, package->getDiffuseColour(), package->getSpecularColour(), package->getDirection());
				} else {
					addDirectionalLight(lightName, package->getDiffuseColour(), package->getSpecularColour(), package->getDirection());
				}
			} else if (pkg->getType()==Package::REMOVE_DIRECTIONAL_LIGHT_PACKAGE_TYPE) {
				RemoveDirectionalLightPackage* package = (RemoveDirectionalLightPackage*) pkg;
				removeDirectionalLight(package->getLightName());
			}
			
			
			// Aufräumen!
			std::cout << "AAA" << std::endl;
			delete pkg;
			std::cout << "BBB" << std::endl;
		}
	}
	
	
	// exit on ESC
	if(keyboard->isKeyDown(OIS::KC_ESCAPE))  {
		std::cout << "BEENDE CHARACTER_PILELINES" << std::endl;
		engineManager->stop();
		std::cout << "BEENDE RENDER LOOP" << std::endl;
		return false; 
	}
	
	
	if (keyboard->isKeyDown(OIS::KC_F)) {
		std::string name = "FatMan";
		if (sceneManager->hasEntity(name)) {
			removeObject(name);
		} else {
			addObject(name, "FatMan.mesh", new Ogre::Vector3(30, -20, -60), new Ogre::Quaternion(1, 0, 0, 1));
		}
	}
		
	
	
	for (CharacterMap::iterator it = getCharacterMap()->begin(); it != getCharacterMap()->end(); it++) {
		it->second->perform();
	}

	
	// Camera Movement
	if (keyboard->isKeyDown(OIS::KC_W)) {
		observer->moveRelative(Ogre::Vector3(0, 0, -1)*25*evt.timeSinceLastFrame);
	}
	if (keyboard->isKeyDown(OIS::KC_S)) {
		observer->moveRelative(Ogre::Vector3(0, 0, 1)*25*evt.timeSinceLastFrame);
	}
	if (keyboard->isKeyDown(OIS::KC_A)) {
		observer->moveRelative(Ogre::Vector3(-1, 0, 0)*25*evt.timeSinceLastFrame);
	}
	if (keyboard->isKeyDown(OIS::KC_D)) {
		observer->moveRelative(Ogre::Vector3(1, 0, 0)*25*evt.timeSinceLastFrame);
	}
	
	
	//observer->calcCurrentPosition();
	observer->yaw(cameraRotX);
	observer->pitch(cameraRotY);
	
	
	return true;
}




bool RenderingLayer::frameEnded(const Ogre::FrameEvent& evt) { 
	return true; 
} 



bool RenderingLayer::processUnbufferedMouseInput(const Ogre::FrameEvent& evt) {
	const OIS::MouseState &ms = mouse->getMouseState();

	cameraRotX = Ogre::Degree(-ms.X.rel * MOUSE_SPEED);
	cameraRotY = Ogre::Degree(-ms.Y.rel * MOUSE_SPEED);
	return true;
}


bool RenderingLayer::keyPressed(const OIS::KeyEvent &evt) {}
bool RenderingLayer::keyReleased(const OIS::KeyEvent &evt) {}


bool RenderingLayer::mouseMoved(const OIS::MouseEvent &evt) {}
bool RenderingLayer::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID) {}
bool RenderingLayer::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID) {}
} // end of namespace