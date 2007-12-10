/*
 *  MessageParser.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 19.08.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "MessageParser.h"

#include "EngineManager.h"


namespace Charanis {

MessageParser::MessageParser(EngineManager* engineManager) 
: Parser::Parser() {
	std::cout << std::endl << std::endl << std::endl << "----------------------------------------------------------------------" << std::endl;
	this->engineManager = engineManager;
}


MessageParser::~MessageParser() {
}


Ogre::ColourValue* MessageParser::getColour(xercesc::DOMElement* parentElement) {
	return new Ogre::ColourValue(
				getRealContents((xercesc::DOMElement*) getNodeList(parentElement, "R")->item(0)), 
				getRealContents((xercesc::DOMElement*) getNodeList(parentElement, "G")->item(0)), 
				getRealContents((xercesc::DOMElement*) getNodeList(parentElement, "B")->item(0))
			);
}


Ogre::Vector3* MessageParser::getVector(xercesc::DOMElement* parentElement) {
	return new Ogre::Vector3(
		getRealContents((xercesc::DOMElement*) getNodeList(parentElement, "X")->item(0)),
		getRealContents((xercesc::DOMElement*) getNodeList(parentElement, "Y")->item(0)),
		getRealContents((xercesc::DOMElement*) getNodeList(parentElement, "Z")->item(0))
	);
}

Ogre::Quaternion* MessageParser::getQuaternion(xercesc::DOMElement* parentElement) {
	return new Ogre::Quaternion(
		getRealContents((xercesc::DOMElement*) getNodeList(parentElement, "W")->item(0)),
		getRealContents((xercesc::DOMElement*) getNodeList(parentElement, "X")->item(0)),
		getRealContents((xercesc::DOMElement*) getNodeList(parentElement, "Y")->item(0)),
		getRealContents((xercesc::DOMElement*) getNodeList(parentElement, "Z")->item(0))
	);
}


void MessageParser::parseSceneControl(xercesc::DOMElement* sceneControlElement, std::vector<Package*>* packageVector) {
	// Camera
	xercesc::DOMNodeList* cameraList = getNodeList(sceneControlElement, "Camera");
	std::cout << "Number of Cameras=" << cameraList->getLength() << std::endl;
	for (int i=0; i<cameraList->getLength(); i++) {
		xercesc::DOMElement* cameraElement = (xercesc::DOMElement*) cameraList->item(i);
		
		xercesc::DOMElement* positionElement = (xercesc::DOMElement*) getNodeList(cameraElement, "Position")->item(0);
		Ogre::Vector3* position = getVector(positionElement);
		
		xercesc::DOMElement* directionElement = (xercesc::DOMElement*) getNodeList(cameraElement, "Direction")->item(0);
		Ogre::Vector3* direction = getVector(directionElement);
		
		//engineManager->controlCamera(position, direction);
		packageVector->push_back(new CameraControlPackage(position, direction));
	}
	
	
	// Adding new Objects
	xercesc::DOMNodeList* newObjectList = getNodeList(sceneControlElement, "AddObject");
	std::cout << "Number of NEW Objects=" << newObjectList->getLength() << std::endl;
	for (int i=0; i<newObjectList->getLength(); i++) {
		xercesc::DOMElement* newObjectElement = (xercesc::DOMElement*) newObjectList->item(i);
		
		
		std::string objectName = getStringContents((xercesc::DOMElement*) getNodeList(newObjectElement, "Name")->item(0));
		std::string modelName = getStringContents((xercesc::DOMElement*) getNodeList(newObjectElement, "ModelName")->item(0));
		
		xercesc::DOMElement* positionElement = (xercesc::DOMElement*) getNodeList(newObjectElement, "Position")->item(0);
		Ogre::Vector3* position = getVector(positionElement);
		
		xercesc::DOMElement* orientationElement = (xercesc::DOMElement*) getNodeList(newObjectElement, "Orientation")->item(0);
		Ogre::Quaternion* orientation = getQuaternion(orientationElement);
		
		Ogre::Real scale = 1;
		if (getNodeList(newObjectElement, "Scale") > 0) {
			scale = getRealContents((xercesc::DOMElement*) getNodeList(newObjectElement, "Scale")->item(0));
		}


		std::cout << "\tObjectName=" << objectName << "      Model=" << modelName << "    Scale=" << scale << std::endl;
		std::cout << "\tPosition  ("<< (*position) << ")" << std::endl;
		std::cout << "\tOrientation  ("<< (*orientation) << ")" << std::endl;
		
		//engineManager->addObject(objectName, modelName, position, orientation, scale);
		AddObjectPackage* package = new AddObjectPackage(objectName, modelName, position, orientation, scale);
		packageVector->push_back(package);
	}
	
	// Removing Objects
	xercesc::DOMNodeList* removeObjectList = getNodeList(sceneControlElement, "RemoveObject");
	std::cout << "Number of Remove-Objects=" << removeObjectList->getLength() << std::endl;
	for (int objectNo=0; objectNo<removeObjectList->getLength(); objectNo++) {
		xercesc::DOMElement* removeObjectElement = (xercesc::DOMElement*) removeObjectList->item(objectNo);
		
		
		std::string objectName = getStringContents((xercesc::DOMElement*) getNodeList(removeObjectElement, "Name")->item(0));
		//engineManager->removeObject(objectName);
		RemoveObjectPackage* package = new RemoveObjectPackage(objectName);
		packageVector->push_back(package);
	}
		
	
	// Adding new Characters
	xercesc::DOMNodeList* newCharacterList = getNodeList(sceneControlElement, "AddCharacter");
	std::cout << "Number of NEW Characters=" << newCharacterList->getLength() << std::endl;
	for (int i=0; i<newCharacterList->getLength(); i++) {
		xercesc::DOMElement* newCharacterElement = (xercesc::DOMElement*) newCharacterList->item(i);
		
		
		std::string characterName = getStringContents((xercesc::DOMElement*) getNodeList(newCharacterElement, "Name")->item(0));
		std::string modelName = getStringContents((xercesc::DOMElement*) getNodeList(newCharacterElement, "ModelName")->item(0));
		
		xercesc::DOMElement* positionElement = (xercesc::DOMElement*) getNodeList(newCharacterElement, "Position")->item(0);
		Ogre::Vector3* position = getVector(positionElement);
		
		xercesc::DOMElement* orientationElement = (xercesc::DOMElement*) getNodeList(newCharacterElement, "Orientation")->item(0);
		Ogre::Vector3* orientation = getVector(orientationElement);

		Ogre::Real scale = 1;
		if (getNodeList(newCharacterElement, "Scale") > 0) {
			scale = getRealContents((xercesc::DOMElement*) getNodeList(newCharacterElement, "Scale")->item(0));
		}
		
		std::cout << "\tCharacterName=" << characterName << "      Model=" << modelName << "    Scale=" << scale << std::endl;
		std::cout << "\tPosition  ("<< *position << ")" << std::endl;
		std::cout << "\tOrientation  ("<< orientation << ")" << std::endl;
		
		engineManager->addCharacter(characterName, modelName, position, orientation, scale);
		
		// importing FEML-Files
		xercesc::DOMNodeList* femlList = getNodeList(newCharacterElement, "FEMLFile");
		for (int j=0; j<femlList->getLength(); j++) {
			xercesc::DOMElement* femlElement = (xercesc::DOMElement*) femlList->item(j);
			std::string femlSrcFile = getStringAttribute(femlElement, "src");
			std::cout << "\tFEML-File=" << femlSrcFile << std::endl;
			
			//engineManager->getDataManager()->getBehaviorLibrary(characterName)->getExpressionLibrary()->importExpressionFile(engineManager->getDataManager()->getConfig()->getFEMLDirectory(), femlSrcFile);
			packageVector->push_back(new ImportFEMLFilePackage(characterName, femlSrcFile));
		}
		
		
		// importing SAML-Files
		xercesc::DOMNodeList* samlList = getNodeList(newCharacterElement, "SAMLFile");
		for (int j=0; j<samlList->getLength(); j++) {
			xercesc::DOMElement* samlElement = (xercesc::DOMElement*) samlList->item(j);
			std::string samlSrcFile = getStringAttribute(samlElement, "src");
			std::cout << "\tSAML-File=" << samlSrcFile << std::endl;
			//engineManager->getDataManager()->getBehaviorLibrary(characterName)->getBodyAnimationLibrary()->importSAMLFile(engineManager->getDataManager()->getConfig()->getSAMLDirectory(), samlSrcFile);
			packageVector->push_back(new ImportSAMLFilePackage(characterName, samlSrcFile));
		}
		
	}
	
	// Removing Characters
	xercesc::DOMNodeList* removeCharacterList = getNodeList(sceneControlElement, "RemoveCharacter");
	std::cout << "Number of Remove-Characters=" << removeCharacterList->getLength() << std::endl;
	for (int characterNo=0; characterNo<removeCharacterList->getLength(); characterNo++) {
		xercesc::DOMElement* removeCharacterElement = (xercesc::DOMElement*) removeCharacterList->item(characterNo);
		
		
		std::string characterName = getStringContents((xercesc::DOMElement*) getNodeList(removeCharacterElement, "Name")->item(0));
		engineManager->removeCharacter(characterName);
		//new RemoveObjectPackage(objectName);
	}
	
	
	// Lights
	if (getNodeList(sceneControlElement, "Lights")->getLength() > 0) {
		xercesc::DOMElement* lightsElement = (xercesc::DOMElement*) getNodeList(sceneControlElement, "Lights")->item(0);
		
		// AmbientLight
		xercesc::DOMNodeList* ambientLightList = getNodeList(lightsElement, "AmbientLight");
		for (int i=0; i<ambientLightList->getLength(); i++) {
			xercesc::DOMElement* ambientElement = (xercesc::DOMElement*) ambientLightList->item(i);
			
			Ogre::ColourValue* ambientColour = getColour((xercesc::DOMElement*) getNodeList(ambientElement, "AmbientColour")->item(0));
			std::cout << "\t\t\tAmbientLight=" << ambientColour << std::endl;
			std::cout << "\t\t\tAmbientLight=" << ambientColour->getAsRGBA() << std::endl;
			AmbientLightPackage* package = new AmbientLightPackage(ambientColour);
			packageVector->push_back(package);
		}
		
		
		// DirectionalLights
		xercesc::DOMNodeList* directionalLightList = getNodeList(lightsElement, "DirectionalLight");
		for (int i=0; i<directionalLightList->getLength(); i++) {
			xercesc::DOMElement* directionalElement = (xercesc::DOMElement*) directionalLightList->item(i);
			
			std::string lightName = getStringContents((xercesc::DOMElement*) getNodeList(directionalElement, "Name")->item(0));
			
			Ogre::ColourValue* diffuseColour = getColour((xercesc::DOMElement*) getNodeList(directionalElement, "DiffuseColour")->item(0));
			Ogre::ColourValue* specularColour = getColour((xercesc::DOMElement*) getNodeList(directionalElement, "SpecularColour")->item(0));
			
			Ogre::Vector3* direction = getVector((xercesc::DOMElement*) getNodeList(directionalElement, "Direction")->item(0));
			
			DirectionalLightPackage* package = new DirectionalLightPackage(lightName, diffuseColour, specularColour, direction);
			packageVector->push_back(package);
		}
		
		// Remove DirectionalLights
		xercesc::DOMNodeList* removeDirectionalLightList = getNodeList(lightsElement, "RemoveDirectionalLight");
		for (int lightNo=0; lightNo<removeDirectionalLightList->getLength(); lightNo++) {
			xercesc::DOMElement* removeDirectionalLightElement = (xercesc::DOMElement*) removeDirectionalLightList->item(lightNo);
			
			std::string lightName = getStringContents((xercesc::DOMElement*) getNodeList(removeDirectionalLightElement, "Name")->item(0));
			RemoveDirectionalLightPackage* package = new RemoveDirectionalLightPackage(lightName);
			packageVector->push_back(package);
		}
	}
}



void MessageParser::parseCharacterControl(xercesc::DOMElement* characterControlElement, std::vector<Package*>* packageVector, Ogre::Real packageLength) {
	xercesc::DOMNodeList *characterList = getNodeList(characterControlElement, "Character");
	std::cout << "NUMBER OF CHARACTERS = " << characterList->getLength() << std::endl;
	
	for (int i=0; i<characterList->getLength(); i++) {
		xercesc::DOMElement* characterElement = (xercesc::DOMElement*) characterList->item(i);
		std::string characterName = getStringContents((xercesc::DOMElement*) getNodeList(characterElement, "Name")->item(0));
		std::cout << "\tCharacter " << characterName << std::endl;
		
		Ogre::Real queueTime = engineManager->getDataManager()->getQueueTime(characterName);
		
		CharacterDataPackage* package = new CharacterDataPackage(characterName, queueTime, queueTime+packageLength);
		packageVector->push_back(package);
		
		if (getNodeList(characterElement, "Emotions")->getLength()>0) {
			xercesc::DOMNodeList* emotionList = getNodeList((xercesc::DOMElement*) getNodeList(characterElement, "Emotions")->item(0), "Emotion");
			std::cout << "\t\tNumber of Emotions = " << emotionList->getLength() << std::endl;
			for (int j=0; j<emotionList->getLength(); j++) {
				xercesc::DOMElement* emotionElement = (xercesc::DOMElement*) emotionList->item(j);
				
				std::string emotionName = getStringContents((xercesc::DOMElement*) getNodeList(emotionElement, "Name")->item(0));
				Ogre::Real time = getRealContents((xercesc::DOMElement*) getNodeList(emotionElement, "Time")->item(0));
				Ogre::Real engineTime = queueTime + time;
				Ogre::Real intensity = getRealContents((xercesc::DOMElement*) getNodeList(emotionElement, "Intensity")->item(0));
				
				std::cout << "\t\t\tEmotion "<< emotionName <<" (Time="<< time <<" (EngineTime="<< engineTime <<")  Intesity="<< intensity <<")" << std::endl;
				
				
				
				EmotionType emotionType = EMOTION_JOY;
				if (emotionName=="joy") {
					emotionType = EMOTION_JOY;
				} else if (emotionName=="sadness") {
					emotionType = EMOTION_SADNESS;
				} else if (emotionName=="anger") { 
					emotionType = EMOTION_ANGER;
				} else if (emotionName=="disgust") {
					emotionType = EMOTION_DISGUST;
				} else if (emotionName=="fear") {
					emotionType = EMOTION_FEAR;
				} else if (emotionName=="surprise") {
					emotionType = EMOTION_SURPRISE;
				} else {
					// TODO: throw exception!!!
				}
				engineManager->getDataManager()->setEmotion(characterName, emotionType, engineTime, intensity);
			}
		}
		
		
		
		if (getNodeList(characterElement, "FacialAnimation")->getLength()>0) {
			xercesc::DOMNodeList* playSoundList = getNodeList(characterElement, "PlaySound");
			for (int j=0; j<playSoundList->getLength(); j++) {
				xercesc::DOMElement* playSoundElement = (xercesc::DOMElement*) playSoundList->item(j);
				std::string fileName = getStringContents((xercesc::DOMElement*) getNodeList(playSoundElement, "FileName")->item(0));
				Ogre::Real startTime = queueTime + getRealContents((xercesc::DOMElement*) getNodeList(playSoundElement, "Time")->item(0));
				
				CharacterSoundPackage* package = new CharacterSoundPackage(characterName, fileName, startTime);
				packageVector->push_back(package);
			}
			
			
			
			xercesc::DOMNodeList* expressionsTrackList = getNodeList((xercesc::DOMElement*) getNodeList(characterElement, "FacialAnimation")->item(0), "ExpressionsTrack");
			std::cout << "\t\tNumber of ExpressionsTracks = " << expressionsTrackList->getLength() << std::endl;
			for (int j=0; j<expressionsTrackList->getLength(); j++) {
				xercesc::DOMElement* expressionsTrackElement = (xercesc::DOMElement*) expressionsTrackList->item(j);
				
				std::string expressionsTrackName = getStringAttribute(expressionsTrackElement, "name");
				std::cout << "\t\t\tExpressionTrack=" << expressionsTrackName << std::endl;
				
				xercesc::DOMNodeList* expressionList = getNodeList(expressionsTrackElement, "Expression");
				std::cout << "\t\t\tNumber of Expressions=" << expressionList->getLength() << std::endl;
				for (int k=0; k<expressionList->getLength(); k++) {
					xercesc::DOMElement* expressionElement = (xercesc::DOMElement*) expressionList->item(k);
					
					std::string expressionName = getStringContents((xercesc::DOMElement*) getNodeList(expressionElement, "Name")->item(0));
					std::cout << "\t\t\t\tExpression=" << expressionName << std::endl;
					
					Ogre::Real expressionTime = queueTime +  getRealContents((xercesc::DOMElement*) getNodeList(expressionElement, "Time")->item(0));
					std::cout << "\t\t\t\tTime=" << expressionTime << std::endl;
					
					Ogre::Real expressionIntensity = 1; // default Value
					if (getNodeList(expressionElement, "Intensity")->getLength() > 0) {
						expressionIntensity = getRealContents((xercesc::DOMElement*) getNodeList(expressionElement, "Intensity")->item(0));
					}
					std::cout << "\t\t\t\tIntensity=" << expressionIntensity << std::endl;
					
					CharacterExpression* expression = new CharacterExpression(expressionTime, 
							engineManager->getDataManager()->getBehaviorLibrary(characterName)->getExpression(expressionName),
							expressionIntensity);
					if (expressionsTrackName == "ControlledFacialExpression") {
						package->addControlledExpression(expression);
					} else if (expressionsTrackName == "Speach") {
						package->addSpeechExpression(expression);
					}
				}
			}
		}
		
		if (getNodeList(characterElement, "BodyAnimation")->getLength()>0) {
			xercesc::DOMElement* bodyAnimationElement = (xercesc::DOMElement*) getNodeList(characterElement, "BodyAnimation")->item(0);
			
			//std::cout << "\t\tBodyAnimation-Parsing not implemented yet" << std::endl;
			
			// ============ PredefinedAnimation
			if (getNodeList(bodyAnimationElement, "PredefinedAnimation")->getLength() > 0) {
				xercesc::DOMNodeList* predefinedAnimationList = getNodeList(bodyAnimationElement, "PredefinedAnimation");
				std::cout << "\t\tNumber of PredefinedAnimations = " << predefinedAnimationList->getLength() << std::endl;
				for (int j=0; j<predefinedAnimationList->getLength(); j++) {
					xercesc::DOMElement* predefinedAnimationElement = (xercesc::DOMElement*) predefinedAnimationList->item(j);
					
					std::string animationName = getStringContents((xercesc::DOMElement*) getNodeList(predefinedAnimationElement, "Name")->item(0));
					std::cout << "\t\t\tPrefefined Animation (" << animationName << ")" << std::endl;
					
					Ogre::Real startTime = queueTime + getRealContents((xercesc::DOMElement*) getNodeList(predefinedAnimationElement, "StartTime")->item(0));
					Ogre::Real endTime = queueTime + getRealContents((xercesc::DOMElement*) getNodeList(predefinedAnimationElement, "EndTime")->item(0));
					std::cout << "\t\t\t\tstart=" << startTime << "    end="<< endTime << std::endl;
					
					
					
					Ogre::Real fadeinTime = 0.5; // default value
					if (getNodeList(predefinedAnimationElement, "FadeinTime")->getLength() > 0) {
						fadeinTime = getRealContents((xercesc::DOMElement*) getNodeList(predefinedAnimationElement, "FadeinTime")->item(0));
					}
					
					Ogre::Real fadeoutTime = 0.5; // default value
					if (getNodeList(predefinedAnimationElement, "FadeoutTime")->getLength() > 0) {
						fadeoutTime = getRealContents((xercesc::DOMElement*) getNodeList(predefinedAnimationElement, "FadeoutTime")->item(0));
					}
					std::cout << "\t\t\t\tfadein=" << fadeinTime << "    fadeout="<< fadeoutTime << std::endl;
					
					Ogre::Real speed = 1; // default value
					if (getNodeList(predefinedAnimationElement, "Speed")->getLength() > 0) {
						speed = getRealContents((xercesc::DOMElement*) getNodeList(predefinedAnimationElement, "Speed")->item(0));
					}
					
					Ogre::Real intensity = 1; // default value
					if (getNodeList(predefinedAnimationElement, "Intensity")->getLength() > 0) {
						intensity = getRealContents((xercesc::DOMElement*) getNodeList(predefinedAnimationElement, "Intensity")->item(0));
					}
					
					Ogre::Real startOffsetTime = 0; // default value
					if (getNodeList(predefinedAnimationElement, "OffsetTime")->getLength() > 0) {
						startOffsetTime = getRealContents((xercesc::DOMElement*) getNodeList(predefinedAnimationElement, "OffsetTime")->item(0));
					}
					
					std::cout << "\t\t\t\tspeed=" << speed << "    intensity=" << intensity << "    offset="<< startOffsetTime << std::endl;
					
					
					CharacterPerformance* cp = new CharacterPerformance(characterName, animationName, startTime, startOffsetTime, fadeinTime, endTime, fadeoutTime, speed);
					cp->setIntensity(intensity);
					package->addCharacterPerformance(cp);
				}
			}
			
			
			
			// ============ InlineAnimation
			if (getNodeList(bodyAnimationElement, "InlineAnimation")->getLength() > 0) {
				xercesc::DOMNodeList* inlineAnimationList = getNodeList(bodyAnimationElement, "InlineAnimation");
				std::cout << "\t\tNumber of InlineAnimations = " << inlineAnimationList->getLength() << std::endl;
				for (int j=0; j<inlineAnimationList->getLength(); j++) {
					xercesc::DOMElement* inlineAnimationElement = (xercesc::DOMElement*) inlineAnimationList->item(j);
					
					
					std::string animationName;
					std::stringstream animationNameStream;
					animationNameStream << "MANUAL_ANIMATION_" << engineManager->getDataManager()->nextManualAnimationId();
					animationNameStream >> animationName;
					

					
					
					Ogre::Real startTime = queueTime + getRealContents((xercesc::DOMElement*) getNodeList(inlineAnimationElement, "StartTime")->item(0));
					Ogre::Real endTime = queueTime + getRealContents((xercesc::DOMElement*) getNodeList(inlineAnimationElement, "EndTime")->item(0));
					std::cout << "\t\t\tstart=" << startTime << "    end="<< endTime << std::endl;
					
					
					Ogre::Real fadeinTime = 0.5; // default value
					if (getNodeList(inlineAnimationElement, "FadeinTime")->getLength() > 0) {
						fadeinTime = getRealContents((xercesc::DOMElement*) getNodeList(inlineAnimationElement, "FadeinTime")->item(0));
					}
					
					Ogre::Real fadeoutTime = 0.5; // default value
					if (getNodeList(inlineAnimationElement, "FadeoutTime")->getLength() > 0) {
						fadeoutTime = getRealContents((xercesc::DOMElement*) getNodeList(inlineAnimationElement, "FadeoutTime")->item(0));
					}
					std::cout << "\t\t\tfadein=" << fadeinTime << "    fadeout="<< fadeoutTime << std::endl;
					
					Ogre::Real speed = 1; // default value
					if (getNodeList(inlineAnimationElement, "Speed")->getLength() > 0) {
						speed = getRealContents((xercesc::DOMElement*) getNodeList(inlineAnimationElement, "Speed")->item(0));
					}
					
					Ogre::Real intensity = 1; // default value
					if (getNodeList(inlineAnimationElement, "Intensity")->getLength() > 0) {
						intensity = getRealContents((xercesc::DOMElement*) getNodeList(inlineAnimationElement, "Intensity")->item(0));
					}
					
					Ogre::Real startOffsetTime = 0; // default value
					if (getNodeList(inlineAnimationElement, "OffsetTime")->getLength() > 0) {
						startOffsetTime = getRealContents((xercesc::DOMElement*) getNodeList(inlineAnimationElement, "OffsetTime")->item(0));
					}
					
					std::cout << "\t\t\tspeed=" << speed << "    intensity=" << intensity << "    offset="<< startOffsetTime << std::endl;
					
					
					
					
					// AnimationDefinition
					xercesc::DOMElement* animationDefinitionElement = (xercesc::DOMElement*) getNodeList(inlineAnimationElement, "AnimationDefinition")->item(0);
					Ogre::Real length = getRealContents((xercesc::DOMElement*) getNodeList(animationDefinitionElement, "Length")->item(0));
					std::cout << "\t\t\tLength=" << length << std::endl;
					
					FKPerformance* fkPerformance = new FKPerformance(animationName, characterName, length);
					package->addFKPerformance(fkPerformance);
					
										
					CharacterPerformance* cp = new CharacterPerformance(characterName, animationName, startTime, startOffsetTime, fadeinTime, endTime, fadeoutTime, speed);
					cp->setIntensity(intensity);
					cp->setManualPerformance(true);
					fkPerformance->setCharacterPerformance(cp);
					
					
					xercesc::DOMNodeList* animationTrackList = getNodeList(animationDefinitionElement, "AnimationTrack");
					std::cout << "\t\t\tNumber of AnimatTracks="<< animationTrackList->getLength() << std::endl;
					for (int j=0; j<animationTrackList->getLength(); j++) {
						xercesc::DOMElement* animationTrackElement = (xercesc::DOMElement*) animationTrackList->item(j);
						
						std::string boneName = getStringContents((xercesc::DOMElement*) getNodeList(animationTrackElement, "BoneName")->item(0));
						std::cout << "\t\t\t\tBone=" << boneName << std::endl;
						
						FKTrack* fkTrack = new FKTrack(boneName);
						fkPerformance->addTrack(fkTrack);
						
						xercesc::DOMNodeList* keyFrameList = getNodeList(animationTrackElement, "KeyFrame");
						std::cout << "\t\t\t\tNumber of KeyFrames=" << keyFrameList->getLength() << std::endl;
						for (int k=0; k<keyFrameList->getLength(); k++) {
							xercesc::DOMElement* keyFrameElement = (xercesc::DOMElement*) keyFrameList->item(k);
							
							Ogre::Real time = getRealContents((xercesc::DOMElement*) getNodeList(keyFrameElement, "Time")->item(0));
							
							xercesc::DOMElement* rotationElement = (xercesc::DOMElement*) getNodeList(keyFrameElement, "Rotation")->item(0);
							Ogre::Quaternion* rotation = getQuaternion(rotationElement);
							
							FKKeyFrame* keyFrame = new FKKeyFrame(time, rotation);// new Ogre::Quaternion(w, x, y, z));
							fkTrack->addKeyFrame(keyFrame);
						}
					}
				}
			}
		}
	}
}


std::vector<Package*>* MessageParser::parseXmlMessage(std::string message) {//, Ogre::Real time) {
	std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
	//xercesc::StringManager sm = xercesc::StringManager();
	std::vector<Package*>* packageVector = new std::vector<Package*>();
	std::map<std::string, Package*> characterPackageMap;
	//CharacterDataPackage* package = NULL;
	
	
	if (parser) {
		parser->setValidationScheme(xercesc::XercesDOMParser::Val_Auto);
		parser->setDoNamespaces(false);
		parser->setDoSchema(false);

		//std::string srcFile = "../../newFormat.xml";
		bool bFailed = false;

		parser->setCreateEntityReferenceNodes(false);
		//parser->setToCreateXMLDeclTypeNode(true);
		try {
			xercesc::MemBufInputSource inputSource((XMLByte*) message.c_str(), message.size(), "1");
			parser->parse(inputSource);
			bFailed = parser->getErrorCount() != 0;
			if (bFailed) {
				std::cerr << "Parsing " << message;
				std::cerr << " error count: " << parser->getErrorCount() << std::endl;
			}
		}
		catch (const xercesc::DOMException& e) {
			std::cerr << "DOM Exception parsing ";
			std::cerr << message;
			std::cerr << " reports: ";
			// was message provided?
			if (e.msg) {
				// yes: display it as ascii.
				char *strMsg = xercesc::XMLString::transcode(e.msg);
				std::cerr << strMsg << std::endl;
				xercesc::XMLString::release(&strMsg);
			}
			else
			// no: just display the error code.
			std::cerr << e.code << std::endl;

			bFailed = true;
		}
		catch (const xercesc::XMLException& e) {
			std::cerr << "XML Exception parsing ";
			std::cerr << message;
			std::cerr << " reports: ";
			std::cerr << e.getMessage() << std::endl;
			bFailed = true;
		}
		catch (const xercesc::SAXException& e) {
			std::cerr << "SAX Exception parsing ";
			std::cerr << message;
			std::cerr << " reports: ";
			std::cerr << e.getMessage() << std::endl;
			bFailed = true;
		}
		catch (...) {
			std::cerr << "An exception parsing ";
			std::cerr << message << std::endl;
			bFailed = true;
		}
		
		std::cout << "%%%%%%%%%%%%%" << std::endl;
		
		// did the input document parse okay?
		if (!bFailed) {
			xercesc::DOMDocument *pDoc = parser->getDocument();
			// insert code to do something with the DOM document here.
			
			xercesc::DOMElement *docElement = pDoc->getDocumentElement();
			char *rootElement = xercesc::XMLString::transcode(docElement->getTagName());
			std::cout << "ROOT: " << xercesc::XMLString::transcode(docElement->getTagName()) << std::endl;
			xercesc::XMLString::release(&rootElement);
			
			// Get the length
			Ogre::Real length = getRealContents((xercesc::DOMElement*) getNodeList(docElement, "Length")->item(0));
			std::cout << "LENGTH="<< length << std::endl;
			
			
			if (getNodeList(docElement, "SystemControl")->getLength() > 0) {
				// TODO: SystemCommands
				std::cout << "parsing System Commands ist not implemented yet" << std::endl;
			}
			
			
			if (getNodeList(docElement, "SceneControl")->getLength() > 0) {
				parseSceneControl((xercesc::DOMElement*) getNodeList(docElement, "SceneControl")->item(0), packageVector);
			}
			
			
			if (getNodeList(docElement, "CharacterControl")->getLength() > 0) {
				parseCharacterControl((xercesc::DOMElement*) getNodeList(docElement, "CharacterControl")->item(0), packageVector, length);
			}
		}
	}
	std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
	return packageVector;
}

} // end of namespace