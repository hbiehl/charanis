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
	
	/*
	std::cout << "======== RANDOM TEST ==========" << std::endl;
	for (int i=0; i<=100; i++) {
		std::cout << i << ". " << dm->randomAlpha() << std::endl;
	}
	*/
	
	loadResources("../../../../cfg/resources.cfg");
	initialize();
	setupScene();
	root->addFrameListener(this);
	
	
	eventProcessor = new Ogre::EventProcessor();
	eventProcessor->initialise(root->getAutoCreatedWindow());
	eventProcessor->addKeyListener(this);
	eventProcessor->addMouseMotionListener(this);
	eventProcessor->startProcessingEvents();
	
	inputReader = eventProcessor->getInputReader();
	
	
	time = 0;
	
	std::cout << "==== ENDE      RenderLoop Konstruktor ====" << std::endl;
}



RenderingLayer::~RenderingLayer() {
	std::cout << "===== Destructor of RenderLoop BEGIN =====" << std::endl;
	delete eventProcessor;
	inputReader = NULL;
	
	CharacterMap::iterator it;
	for (it = characterMap->begin(); it!=characterMap->end(); it++) {
		std::cout << "deleting character " << (*it).first << std::endl;
		delete (*it).second;
	}
	characterMap->clear();
	
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
	root->initialise(true, "Simple Ogre App");
	
	sceneManager = root->createSceneManager(sceneType, "GenericSceneManager");
	//sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
	sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_MODULATIVE);
	
	observer = new Observer(dataManager, root, sceneManager);
	
	
	
		
	Ogre::Animation::setDefaultInterpolationMode(Ogre::Animation::IM_LINEAR);
	Ogre::Animation::setDefaultRotationInterpolationMode(Ogre::Animation::RIM_LINEAR);
	
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	
	Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();

	// Create a panel
	Ogre::OverlayContainer* panel = static_cast<Ogre::OverlayContainer*>(
		Ogre::OverlayManager::getSingleton().createOverlayElement("Panel", "PanelName"));
	panel->setMetricsMode(Ogre::GMM_PIXELS);
	panel->setPosition(10, 10);
	panel->setDimensions(100, 100);
	//panel->setMaterialName("Examples/RustySteel"); // Optional background material


	// Create a text area
	timeTextArea = static_cast<Ogre::TextAreaOverlayElement*>(
		Ogre::OverlayManager::getSingleton().createOverlayElement("TextArea", "TimeTextArea"));
	timeTextArea->setMetricsMode(Ogre::GMM_PIXELS);
	timeTextArea->setPosition(10, 10);
	timeTextArea->setDimensions(80, 30);
	timeTextArea->setCaption("0");
	//timeTextArea->setHorizontalAlignment(Ogre::GHA_RIGHT);
	timeTextArea->setCharHeight(20);
	//timeTextArea->setFontName("IronMaiden");
	timeTextArea->setFontName("StarWars");
	//timeTextArea->setFontName("Ogre");
	timeTextArea->setColourBottom(Ogre::ColourValue(0.8, 0, 0));
	timeTextArea->setColourTop(Ogre::ColourValue(1, 0.7, 0));



	characterTextArea = static_cast<Ogre::TextAreaOverlayElement*>(
		Ogre::OverlayManager::getSingleton().createOverlayElement("TextArea", "CharacterTextArea"));
	characterTextArea->setMetricsMode(Ogre::GMM_PIXELS);
	characterTextArea->setPosition(10, 50);
	characterTextArea->setDimensions(80, 100);
	characterTextArea->setCaption("---");
	//timeTextArea->setHorizontalAlignment(Ogre::GHA_RIGHT);
	characterTextArea->setCharHeight(20);
	//timeTextArea->setFontName("IronMaiden");
	characterTextArea->setFontName("StarWars");
	//timeTextArea->setFontName("Ogre");
	characterTextArea->setColourBottom(Ogre::ColourValue(0.8, 0, 0));
	characterTextArea->setColourTop(Ogre::ColourValue(1, 0.7, 0));

	

	// Create an overlay, and add the panel
	Ogre::Overlay* overlay = Ogre::OverlayManager::getSingleton().create("OverlayName");
	overlay->add2D(panel);

	// Add the text area to the panel
	panel->addChild(timeTextArea);
	panel->addChild(characterTextArea);

	// Show the overlay
	overlay->show();
	
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
	//floorEnt->setMaterialName("Examples/RustySteel");
	floorEnt->setMaterialName("Examples/Rockwall");
	floorEnt->setCastShadows(false);
	sceneManager->getRootSceneNode()->attachObject(floorEnt);

	// Fog
	// sceneMgr->setFog(Ogre::FOG_EXP2);
	
	// Sky
	sceneManager->setSkyDome(true, "Examples/CloudySky", 5, 8);
	
	
	/*
	Ogre::SceneNode *eyeNode = sceneManager->getRootSceneNode()->createChildSceneNode("eyeNode");
	eyeNode->setPosition(30, 0, -30);
	eyeNode->setScale(10, 10, 10);
	Ogre::Entity* eyeEntity = sceneManager->createEntity("LEYE", "BlueEye.mesh");
	eyeNode->attachObject(eyeEntity);
	eyeEntity->setCastShadows(true);
*/
	
	//addObject("Trashbin", "Trashbin.mesh", new Ogre::Vector3(0,-50,0), new Ogre::Quaternion(0.5, 1, 0, 0));
	
	
	/*
	// Robbie the robot
	Character* robbie = addCharacter("Robbie", "robot.mesh", Ogre::Vector3(0, -50, 0), Ogre::Vector3(1,0,-1));
	BehaviorLibrary* behaviorLib = dataManager->getBehaviorLibrary(robbie->getName());
	FacialExpression* exp = new FacialExpression("neutral");
	behaviorLib->addExpression(exp);
	
	exp = new FacialExpression("joy");
	exp->setWeight(AU_1, 1.0);
	behaviorLib->addExpression(exp);
	
	exp = new FacialExpression("sadness");
	exp->setWeight(AU_2, 1.0);
	behaviorLib->addExpression(exp);
	
	
	addCharacter("Herrmann", "robot.mesh", Ogre::Vector3(-80, -50, -40), Ogre::Vector3(1,0,-0.3));
	//addCharacter("Quentin", "ninja.mesh", Ogre::Vector3(40, -50, 10), Ogre::Vector3(-1,0,0.5), 0.2);
	
	
	//addCharacter("Fleur", "Plane.008.mesh", Ogre::Vector3(-40, 50, 20), Ogre::Vector3(0,-1,0)); // OK
	addCharacter("MyHuman", "Mesh.mesh", Ogre::Vector3(-40, 0, 20), Ogre::Vector3(0,-1,0)); // OK
	
	
	//addCharacter("Blendo", "Plane.003.mesh", Ogre::Vector3(-40, 0, 20), Ogre::Vector3(0,-1,0));
	//addCharacter("Vamp", "Mesh.001.mesh", Ogre::Vector3(-40, 0, 20), Ogre::Vector3(0,-1,0));
	
	
	
	//addCharacter("Swimmer", "Plane.003.mesh", Ogre::Vector3(-40, 50, 20), Ogre::Vector3(0,-1,0));
	
	
	
	//addCharacter("Man", "cuerpo.mesh", Ogre::Vector3(-40, 0, 20), Ogre::Vector3(0,-1,0), 20);
	//addCharacter("Man", "male.mesh", Ogre::Vector3(-40, 50, 20), Ogre::Vector3(0,-1,0));
	
	
	
	//addCharacter("Joe", "jaiqua.mesh", Ogre::Vector3(-40, -50, 30), Ogre::Vector3(-1,0,0.5), 2);
	//addCharacter("Harald", "fish.mesh", Ogre::Vector3(70, -50, -30), Ogre::Vector3(-1,0,0), 10);
	

	
	// ===== BEGIN Test Facial Animation ===============================================================
	unsigned short poseIndexes[18] = { 1, 2, 3, 4, 7, 8, 6, 5, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18};
	Ogre::MeshPtr mesh = Ogre::MeshManager::getSingleton().load("facial.mesh", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	//mesh->clone("firstFaceTest.mesh", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	//mesh = Ogre::MeshManager::getSingleton().load("firstFaceTest.mesh", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	
	for (int i=0; i<mesh->getPoseCount(); i++) {
		Ogre::Pose* pose = mesh->getPose(i);
		std::cout << "*************************************************** POSE " << i << ": " << pose->getName() << std::endl;
	}
	for (int i=0; i<mesh->getNumSubMeshes(); i++) {
		Ogre::SubMesh* subMesh = mesh->getSubMesh(i);
		std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> SubMesh " << i << ": " << subMesh->getMaterialName() << std::endl;
	}
	
	
	Ogre::Animation* anim = mesh->createAnimation("manual", 6);
	Ogre::VertexAnimationTrack* track = anim->createVertexTrack(4, Ogre::VAT_POSE);
	//Ogre::VertexPoseKeyFrame* manualKeyFrame = track->createVertexPoseKeyFrame(0);
	// create pose references, initially zero
	FacialExpression neutralExpr = FacialExpression("neutral");
	FacialExpression joyExpr = FacialExpression("joy");
	joyExpr.setWeight(AU_1, 1.0);
	FacialExpression sadnessExpr = FacialExpression("sadness");
	sadnessExpr.setWeight(AU_2, 1.0);
	
	
	neutralExpr.createKeyFrame(track, 0);
	joyExpr.createKeyFrame(track, 1);
	sadnessExpr.createKeyFrame(track, 3);

	
	facialEntity = sceneManager->createEntity("Facial", "facial.mesh");
	facialEntity->setCastShadows(false);
	Ogre::SceneNode *facialNode = sceneManager->getRootSceneNode()->createChildSceneNode("facialNode");
	facialNode->attachObject(facialEntity);
	facialNode->setPosition(30, 0, -30);
	
	//facialEntity->getAnimationState("manual")->setLoop(false);
	
	facialEntity->getAnimationState("manual")->setEnabled(true);
	facialEntity->getAnimationState("manual")->setTimePosition(0);
	
	facialEntity->getAnimationState("Speak")->setEnabled(true);
	// ===== END TEST ==================================================================================
	
	*/
	
	// add WayPoint to Robbie
	/*
	robbie->addWayPoint(Ogre::Vector3(90, -50, 20));
	Ogre::Entity* ent = sceneManager->createEntity("wp1", "robot.mesh");
	Ogre::SceneNode *node = sceneManager->getRootSceneNode()->createChildSceneNode("wp1Node");
	node->attachObject(ent);
	node->setScale(0.1, 0.1, 0.1);
	node->setPosition(90, -50, 20);
	
	robbie->addWayPoint(Ogre::Vector3(30, -50, -260));
	ent = sceneManager->createEntity("wp2", "robot.mesh");
	node = sceneManager->getRootSceneNode()->createChildSceneNode("wp2Node");
	node->attachObject(ent);
	node->setScale(0.1, 0.1, 0.1);
	node->setPosition(30, -50, -260);
	
	robbie->addWayPoint(Ogre::Vector3(120, -50, -290));
	ent = sceneManager->createEntity("wp3", "robot.mesh");
	node = sceneManager->getRootSceneNode()->createChildSceneNode("wp3Node");
	node->attachObject(ent);
	node->setScale(0.1, 0.1, 0.1);
	node->setPosition(120, -50, -290);
	
	robbie->addWayPoint(Ogre::Vector3(-30, -50, -50));
	ent = sceneManager->createEntity("wp4", "robot.mesh");
	node = sceneManager->getRootSceneNode()->createChildSceneNode("wp4Node");
	node->attachObject(ent);
	node->setScale(0.1, 0.1, 0.1);
	node->setPosition(-30, -50, -50);
	*/
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
	std::string caption = "";
	for (CharacterMap::iterator it = characterMap->begin(); it != characterMap->end(); it++) {
		caption += it->first + "\n";
	}
	characterTextArea->setCaption(caption);
}


void RenderingLayer::updateTimeStats(long time) {
	timeTextArea->setCaption(Ogre::StringConverter::toString(time));
}



void RenderingLayer::run() {
	root->startRendering();
}


bool RenderingLayer::frameStarted(const Ogre::FrameEvent& evt) {
	//std::cout << "frame started" << std::endl;
	inputReader->capture();
	
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
	if(inputReader->isKeyDown(Ogre::KC_ESCAPE))  {
		std::cout << "BEENDE CHARACTER_PILELINES" << std::endl;
		engineManager->stop();
		std::cout << "BEENDE RENDER LOOP" << std::endl;
		return false; 
	}
	
	
	if (inputReader->isKeyDown(Ogre::KC_F)) {
		std::string name = "FatMan";
		if (sceneManager->hasEntity(name)) {
			removeObject(name);
		} else {
			addObject(name, "FatMan.mesh", new Ogre::Vector3(30, -20, -60), new Ogre::Quaternion(1, 0, 0, 1));
		}
	}
		
	
	
	for (CharacterMap::iterator it = getCharacterMap()->begin(); it != getCharacterMap()->end(); it++) {
		//it->second->perform(evt.timeSinceLastFrame);
		it->second->perform();
	}


/*
	if (inputReader->isKeyDown(Ogre::KC_P)) {
		getCharacter("Robbie")->addAudioTrack(new AudioTrack("../../sound_electric.wav", time));
		//getCharacter("Robbie")->playAudioTrack(new AudioTrack("../../sound_electric.wav", time));
	}
*/

	if (inputReader->isKeyDown(Ogre::KC_SPACE)) {
		getCharacter("Robbie")->walkPath(evt.timeSinceLastFrame);
	}
	
	
	// Camera Movement
	if (inputReader->isKeyDown(Ogre::KC_W)) {
		observer->moveRelative(Ogre::Vector3(0, 0, -1)*25*evt.timeSinceLastFrame);
	}
	if (inputReader->isKeyDown(Ogre::KC_S)) {
		observer->moveRelative(Ogre::Vector3(0, 0, 1)*25*evt.timeSinceLastFrame);
	}
	if (inputReader->isKeyDown(Ogre::KC_A)) {
		observer->moveRelative(Ogre::Vector3(-1, 0, 0)*25*evt.timeSinceLastFrame);
	}
	if (inputReader->isKeyDown(Ogre::KC_D)) {
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
	//std::cout << "!!! MOUSE  |" << inputReader->getMouseRelativeX() << "|" << inputReader->getMouseRelativeY() << std::endl;
	
	return true;
}





void RenderingLayer::keyClicked(Ogre::KeyEvent* e) {}
void RenderingLayer::keyPressed(Ogre::KeyEvent* e) {}
void RenderingLayer::keyReleased(Ogre::KeyEvent* e) {}


void RenderingLayer::mouseMoved(Ogre::MouseEvent *e) {
	cameraRotX = Ogre::Degree(- e->getRelX() * MOUSE_SPEED);
	cameraRotY = Ogre::Degree(- e->getRelY() * MOUSE_SPEED);
}

void RenderingLayer::mouseDragged(Ogre::MouseEvent *e) {}
void RenderingLayer::mouseDragMoved(Ogre::MouseEvent *e) {}

} // end of namespace