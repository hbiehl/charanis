/*
 *  Character.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 01.02.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "Character.h"

// std includes
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>

// dependency includes
#include <Ogre/OgreSkeletonSerializer.h>
#include <Ogre/OgreTagPoint.h>

// project includes
#include "Config.h"
#include "BehaviorLibrary.h"
#include "BodyAnimation.h"
#include "BodyAnimationVector.h"
#include "CharacterPerformance.h"
#include "DataManager.h"
#include "ExpressionLibrary.h"
#include "FacialExpression.h"
#include "FKPerformance.h"
#include "FEMLParser.h"
#include "SAMLParser.h"

namespace Charanis {

Character::Character(Ogre::SceneManager* sceneManager, Ogre::SceneNode* parentNode, std::string meshName, DataManager* dm, std::string name, Ogre::Real scale)
		: DISTANCE_TOLERANCE(1) {
	std::cout << "===== Constructor Character ("<< name << ") ====" << std::endl;
	this->name = name;
	this->sceneManager = sceneManager;
	this->dataManager = dm;
	
	BehaviorLibrary* bl = dataManager->getBehaviorLibrary(name);
	ExpressionLibrary* expressionLibrary = bl->getExpressionLibrary();
	StringIntMap* poseMapping = expressionLibrary->getPoseMapping();
	// TODO: currently poseMapping not used?!?

	facialEntity = NULL;
	std::string myPrivateMeshName = name +"_"+ meshName;
	Ogre::MeshPtr origMesh = Ogre::MeshManager::getSingleton().load(meshName, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	Ogre::MeshPtr characterMesh = origMesh->clone(myPrivateMeshName);

	// add the poses of the model (vertex morph targets) to BehaviourLibrary/ExpressionLibrary	
	for (int i=0; i<characterMesh->getPoseCount(); i++) {
		Ogre::Pose* pose = characterMesh->getPose(i);
		std::cout << "Adding Pose " << pose->getName() << " at index " << i << std::endl;
		expressionLibrary->addPoseMapping(pose->getName(), i);
	}
	createFacialAnimations(characterMesh);
	//entity->_initialise(true);

	// create the entity
	entity = sceneManager->createEntity(name, myPrivateMeshName);
	entity->setCastShadows(false); // TODO: workaround because of too low shadow buffer (too many vertices)
	// ... and add it to the scene
	sceneNode = parentNode->createChildSceneNode(name+"Node");
	sceneNode->setScale(scale, scale, scale);
	sceneNode->attachObject(entity);
	
    /*
	// set some parameters of the entity
	//entity->setCastShadows(true);
	entity->getSkeleton()->setBlendMode(Ogre::ANIMBLEND_CUMULATIVE);
	facialEntity = entity; //TODO temporary hack
	
    std::cout << "Character::Character --"
        << " ent="  << entity 
        << " skel=" << entity->getSkeleton() 
        << " node="<< sceneNode 
        << std::endl;
	
	
    // add the skeleton animations of the model to BehaviourLibrary
	std::cout << "Available Animations for Character " << name << ":" << std::endl;
	Ogre::AnimationStateIterator it = entity->getAllAnimationStates()->getAnimationStateIterator();
	while (it.hasMoreElements()) {
		Ogre::AnimationState* animState = it.getNext();
		bl->addBodyAnimation(new BodyAnimation(animState->getAnimationName()));
	}
	bl->printBodyAnimations();
	*/
    
    // ======================= only needed because hacky model ===============
	// add Eyes to the model
	//addEyes(meshName);

	// output some helpful information about the model
	printBones();
	printMeshes();
	printMeshAnimations();
	printAnimationStates();
	
	
	/*
	for (int i=0; i<EMOTION_END; i++) {
		std::stringstream animationNameStream;
		std::string animationName;
		animationNameStream << "emotion_" << i;
		animationNameStream >> animationName;
		
		facialEntity->getAnimationState(animationName)->setEnabled(true);
		facialEntity->getAnimationState(animationName)->setTimePosition(0);
	}
	
	facialEntity->getAnimationState("speech")->setEnabled(true);
	facialEntity->getAnimationState("speech")->setTimePosition(0);
	
	facialEntity->getAnimationState("controlledExpression")->setEnabled(true);
	facialEntity->getAnimationState("controlledExpression")->setTimePosition(0);
	*/
	

	// ----------- Audio Stuff ----------
	// Ein OpenAL-Audio-Source generieren...
	std::cout << "OpenAL: Generating Source..." << std::endl;

	int error;
	alGenSources(1, audioSource);
	if ((error = alGetError()) != AL_NO_ERROR) {
		std::cout << "alGenSources : " << error << std::endl;
		exit(0);
	}
	
	float refDist = 30;
	alSourcef(audioSource[0], AL_REFERENCE_DISTANCE, refDist);
	std::cout << "Character::Character   -   alSourcef(audioSource[0], AL_REFERENCE_DISTANCE, refDist);" << alGetError()  << std::endl;
	
	
	currentAudioTrack = NULL;
	
	// play an audioTrack to test if audio is working. TODO: These lines need to be removed for release
	std::string filename = "../CLEAN_UP/sound_engine.wav";
	if (name=="Robbie") {
		filename = "../CLEAN_UP/sound_electric.wav";
	}
	//playAudioTrack(new AudioTrack(filename, 0));
	
	std::cout << "===== Constructor Character ("<< name << ") DONE ====" << std::endl;
}



Character::~Character() {
	std::cout << "===== Destructor Character ("<< name << ") ====" << std::endl;
	
	alSourceStop(audioSource[0]);
	if (currentAudioTrack != NULL) {
		delete currentAudioTrack;
	}
	alDeleteSources(1, audioSource);
	
	
	dataManager->removeCharacter(name);
	
	
	if (entity->getMesh()->getName() == "robot.mesh") {
		//entity->detachObjectFromBone(facialEntity->getName());
		
		if (leftEyeEntity!=NULL) {
			entity->detachObjectFromBone(leftEyeEntity->getName());
		}
		
		if (leftEyeEntity!=NULL) {
			entity->detachObjectFromBone(rightEyeEntity->getName());
		}
	} else if (entity->getMesh()->getName() == "Charanis.001.mesh") {
		//entity->detachObjectFromBone(facialEntity->getName());
		
		if (leftEyeEntity!=NULL) {
			entity->detachObjectFromBone(leftEyeEntity->getName());
		}
		
		if (leftEyeEntity!=NULL) {
			entity->detachObjectFromBone(rightEyeEntity->getName());
		}
	}
	
	
	std::cout << "removing object "<< name << " from scene BEGIN" << std::endl;
	sceneNode->detachObject(entity);
	std::cout << "destroying entity" << std::endl;
	//sceneManager->destroyEntity(entity->getName());
	sceneManager->destroyEntity(entity);
	entity = NULL;
	std::cout << "removing object "<< name << " from scene END" << std::endl;

	std::cout << "removing sceneNode of object "<< name << " from scene BEGIN" << std::endl;
	sceneNode->getParentSceneNode()->removeAndDestroyChild(sceneNode->getName());
	sceneNode = NULL;
	std::cout << "removing sceneNode of object "<< name << " from scene END" << std::endl;
	
	
	std::cout << "deleting CharacterPerformance-Objects of " << name << "    BEGIN" << std::endl;
	// Delete characterPerformance-Objects
	for (CharacterPerformanceVector::iterator it = characterPerformanceVector.begin(); it!=characterPerformanceVector.end(); it++) {
		delete *it;
	}
	characterPerformanceVector.clear();
	std::cout << "deleting CharacterPerformance-Objects of " << name << "    END" << std::endl;
	

	std::cout << "===== Destructor Character ("<< name << ") DONE ====" << std::endl;
}



void Character::addEyes(const std::string& meshName) {
	/*========== AUGEN EINFUEGEN ===============*/
	if (meshName == "robot.mesh") {
		Ogre::Bone* bone = entity->getSkeleton()->createBone("l_eyeball_joint", 18);
		entity->getSkeleton()->getBone("Joint12")->addChild(bone);
		bone->translate(Ogre::Vector3(0, 30, -10));
		bone->rotate(Ogre::Vector3(0,1,0), Ogre::Radian(Ogre::Degree(90)));
		bone->setInitialState();
		leftEyeEntity = sceneManager->createEntity(name+"_LEYE", "BlueEye.mesh");
		leftEyeEntity->setCastShadows(true);
		Ogre::TagPoint* tp = entity->attachObjectToBone("l_eyeball_joint", leftEyeEntity);
		tp->setScale(2, 2, 2);
		
		
		bone = entity->getSkeleton()->createBone("r_eyeball_joint", 19);
		entity->getSkeleton()->getBone("Joint12")->addChild(bone);
		bone->translate(Ogre::Vector3(0, 30, 10));
		bone->rotate(Ogre::Vector3(0,1,0), Ogre::Radian(Ogre::Degree(90)));
		bone->setInitialState();
		rightEyeEntity = sceneManager->createEntity(name+"_REYE", "BlueEye.mesh");
		rightEyeEntity->setCastShadows(true);
		tp = entity->attachObjectToBone("r_eyeball_joint", rightEyeEntity);
		tp->setScale(2, 2, 2);
	} else if (meshName == "Charanis.001.mesh") {
		Ogre::Bone* bone = entity->getSkeleton()->createBone("l_eyeball_joint", 21);
		entity->getSkeleton()->getBone("scullbase")->addChild(bone);
		bone->translate(Ogre::Vector3(-1, 3, 0));
		//bone->rotate(Ogre::Vector3(0,1,0), Ogre::Radian(Ogre::Degree(90)));
		bone->setInitialState();
		leftEyeEntity = sceneManager->createEntity(name+"_LEYE", "BlueEye.mesh");
		leftEyeEntity->setCastShadows(true);
		Ogre::TagPoint* tp = entity->attachObjectToBone("l_eyeball_joint", leftEyeEntity);
		tp->setScale(0.2, 0.2, 0.2);
		
		
		bone = entity->getSkeleton()->createBone("r_eyeball_joint", 22);
		entity->getSkeleton()->getBone("scullbase")->addChild(bone);
		bone->translate(Ogre::Vector3(1, 3, 0));
		//bone->rotate(Ogre::Vector3(0,1,0), Ogre::Radian(Ogre::Degree(90)));
		bone->setInitialState();
		rightEyeEntity = sceneManager->createEntity(name+"_REYE", "BlueEye.mesh");
		rightEyeEntity->setCastShadows(true);
		tp = entity->attachObjectToBone("r_eyeball_joint", rightEyeEntity);
		tp->setScale(0.2, 0.2, 0.2);
	} else {
		leftEyeEntity = NULL;
		rightEyeEntity = NULL;
	}
}


void Character::createFacialAnimations(Ogre::MeshPtr& newMesh) {
	//Ogre::Mesh* newMesh = facialMesh;
	BehaviorLibrary* bl = dataManager->getBehaviorLibrary(name);
	StringIntMap* poseMapping = bl->getExpressionLibrary()->getPoseMapping();
	
	//==== Emotionen-Animationen und die KeyFrames anlegen
	for (int i=0; i<EMOTION_END; i++) {
		std::stringstream animationNameStream;
		std::string animationName;
		animationNameStream << "emotion_" << i;
		animationNameStream >> animationName;
		std::cout << "creating animation " << animationName << std::endl;
		Ogre::Animation* emotionAnim = newMesh->createAnimation(animationName, 0);
		Ogre::VertexAnimationTrack* emotionTrack = emotionAnim->createVertexTrack(4, Ogre::VAT_POSE);
		emotionKeyFrameMap[EmotionType(i)] = emotionTrack->createVertexPoseKeyFrame(0);
		
		StringIntMap::iterator it = poseMapping->begin();
		for (; it!=poseMapping->end(); it++) {
			emotionKeyFrameMap[EmotionType(i)]->addPoseReference(it->second, 0);
		}
	}

	//==== Sprach-Animation anlegen
	Ogre::Animation* speechAnim = newMesh->createAnimation("speech", 0);
	Ogre::VertexAnimationTrack* speechTrack = speechAnim->createVertexTrack(4, Ogre::VAT_POSE);
	speechKeyFrame = speechTrack->createVertexPoseKeyFrame(0);
	
	// neutralen Gesichtsausdruck als Start anlegen
	speechExpressionMap[0] = new CharacterExpression(0, bl->getExpression("neutral"), 1);


	//==== Controlled Animation anlegen
	Ogre::Animation* controlledExpressionAnim = newMesh->createAnimation("controlledExpression", 0);
	Ogre::VertexAnimationTrack* controlledExpressionTrack = controlledExpressionAnim->createVertexTrack(4, Ogre::VAT_POSE);
	controlledExpressionKeyFrame = controlledExpressionTrack->createVertexPoseKeyFrame(0);
	
	controlledExpressionMap[0] = new CharacterExpression(0, bl->getExpression("neutral"), 1);
}


void Character::printBones() {
	std::cout << "Skeleton of Character " << name << ":" << std::endl;
	Ogre::Skeleton::BoneIterator boneIt = entity->getSkeleton()->getBoneIterator();
	while (boneIt.hasMoreElements()) {
		Ogre::Bone* bone = boneIt.getNext();
		std::cout << "----- " << bone->getName() << " ("<< bone->getHandle() << ")" << std::endl;
	}
}

void Character::printMeshes() {
	// just output some useful info: all meshes of the character
	std::cout << "Meshes of Character " << name << ":" << std::endl;
	Ogre::Mesh::SubMeshNameMap m = entity->getMesh()->getSubMeshNameMap();
	for (Ogre::Mesh::SubMeshNameMap::iterator it = m.begin(); it!=m.end(); it++) {
		Ogre::SubMesh* subMesh = entity->getMesh()->getSubMesh(it->second);
		std::cout << "----- "<< it->second << " name=" << it->first << " mat=" << subMesh->getMaterialName() << std::endl;
	}
}

void Character::printMeshAnimations() {
	std::cout << "Mesh Animations of Character " << name << ":" << std::endl;
	for (int i=0; i<entity->getMesh()->getNumAnimations(); i++) {
		std::cout << "----- "<< i << " " << entity->getMesh()->getAnimation(i)->getName() << std::endl;
	}
}

void Character::printAnimationStates() {
	std::cout << "Animation States of Character " << name << ":" << std::endl;
	Ogre::AnimationStateIterator it = entity->getAllAnimationStates()->getAnimationStateIterator();
	while (it.hasMoreElements()) {
		Ogre::AnimationState* animstate = it.getNext();
		std::cout << "----- "<< animstate->getAnimationName() << std::endl;
	}
}

void Character::importFEMLFile(std::string fileName) {
	std::cout << "Character::importFEMLFile("<<fileName<<")   Character=" << name << std::endl;
	
	FEMLParser parser = FEMLParser(dataManager->getConfig()->getFEMLDirectory());
	
	FacialExpressionVector* feVec = parser.parseFile(fileName);
	for (FacialExpressionVector::iterator it=feVec->begin(); it!=feVec->end(); it++) {
		dataManager->getBehaviorLibrary(name)->getExpressionLibrary()->addExpression(*it);
	}
	feVec->clear();
	delete feVec;
}



void Character::importSAMLFile(std::string fileName) {
	std::cout << "Character::importSAMLFile("<<fileName<<")   Character=" << name << std::endl;
	SAMLParser parser = SAMLParser(dataManager->getConfig()->getSAMLDirectory());
	
	BodyAnimationVector* baVec = parser.parseFile(entity, fileName);
	for (BodyAnimationVector::iterator it=baVec->begin(); it!=baVec->end(); it++) {
		dataManager->getBehaviorLibrary(name)->getBodyAnimationLibrary()->addBodyAnimation(*it);
	}
	baVec->clear();
	delete baVec;
}





void Character::playAudioTrack(AudioTrack* track) {
	std::cout << "Character::playAudioTrack(..) BEGIN" << std::endl;
	int error;
	alSourceStop(audioSource[0]);
	std::cout << "Character::playAudioTrack(AudioTrack* track)   -   alSourceStop(audioSource[0]);" << alGetError()  << std::endl;
	

	std::cout << "Attaching Source..." << std::endl;
	alSourcei(audioSource[0], AL_BUFFER, track->getBuffer());
	if ((error = alGetError()) != AL_NO_ERROR) {
		std::cout << "alSourcei : " <<  error << std::endl;
		exit(0);
	}
	
	if (currentAudioTrack != NULL) {
		//alSourceUnqueueBuffers(audioSource[0], 1, currentAudioTrack->getBuffer());
		delete currentAudioTrack;
	}
	currentAudioTrack = track;
	
	
	alSourcei(audioSource[0], AL_LOOPING, AL_FALSE);
	std::cout << "Character::playAudioTrack(AudioTrack* track)   -   alSourcei(audioSource[0], AL_LOOPING, AL_FALSE);" << alGetError()  << std::endl;
	
	
	alSourcePlay(audioSource[0]);
	std::cout << "Character::playAudioTrack(AudioTrack* track)   -   alSourcePlay(audioSource[0]);" << alGetError()  << std::endl;
	std::cout << "Character::playAudioTrack(..) END" << std::endl;
}




std::string Character::getName() {
	return name;
}



void Character::setPosition(const Ogre::Vector3 pos) {
	sceneNode->setPosition(pos);
	float vec[3];
	vec[0] = pos.x;
	vec[1] = entity->getWorldBoundingBox().getMaximum().y; //pos.y;
	vec[2] = pos.z;
	alSourcefv(audioSource[0], AL_POSITION, vec);
}




Ogre::Vector3 Character::getPosition() {
	return sceneNode->getPosition();
}



void Character::addFKPerformance(FKPerformance* performance) {
	std::cout << "addFKPerformance - BEGIN" << std::endl;
	
	// create Animation out of FKPerformance
	Ogre::Animation* anim = performance->createOgreAnimation(entity);
	entity->refreshAvailableAnimationState();
	// TODO: currently variable anim not used?!?
	
	addPerformance(performance->getCharacterPerformance());
	std::cout << "addFKPerformance - END" << std::endl;
}


void Character::addFKPerformances(FKPerformanceVector* performanceVec) {
	std::cout << "Character::addFKPerformances() BEGIN" << std::endl;
	for (FKPerformanceVector::iterator it = performanceVec->begin(); it != performanceVec->end(); it++) {
		addFKPerformance(*it);
	}
	std::cout << "Character::addFKPerformances() END" << std::endl;
}


void Character::addPerformance(CharacterPerformance* performance) {
	characterPerformanceVector.push_back(performance);
}


void Character::addPerformances(CharacterPerformanceVector* performanceVec) {
	for (CharacterPerformanceVector::iterator it = performanceVec->begin(); it != performanceVec->end(); it++) {
		addPerformance(*it);
	}	
}


void Character::addSpeechExpression(CharacterExpression* exp) {
	speechExpressionMap[exp->getTime()] = exp;
}


void Character::addSpeechExpressions(TimedExpressionMap* expressionMap) {
	for (TimedExpressionMap::iterator it = expressionMap->begin(); it != expressionMap->end(); it++) {
		addSpeechExpression(it->second);
	}
}


void Character::addControlledExpression(CharacterExpression* exp) {
	controlledExpressionMap[exp->getTime()] = exp;
}

void Character::addControlledExpressions(TimedExpressionMap* expressionMap) {
	for (TimedExpressionMap::iterator it = expressionMap->begin(); it != expressionMap->end(); it++) {
		addControlledExpression(it->second);
	}
}


void Character::addAudioTrack(AudioTrack* track) {
	audioTrackMap[track->getStartTime()] = track;
}


void Character::playAnimations() {
	//std::cout << "<<<<<<< BEGIN Character.playAnimations >>>>>>>>>>>>>" << std::endl;
	Ogre::Real time = dataManager->getEngineTime();
	CharacterPerformanceVector::iterator it = characterPerformanceVector.begin();
	while  (it!=characterPerformanceVector.end()) {		
		CharacterPerformance* performance = *it;
		std::string animationName = performance->getAnimationName();
		
		std::cout << "playing animation " << animationName << std::endl;
		
		try {
			entity->getAnimationState(animationName);
		} catch (...) {
			std::cout << "!!!!!!!!!!!!!! ERROR: Animation '" << animationName << "' does not exist in Character '" << name << "' !!!!!!!!!!!!!!!!" << std::endl; 
			it = characterPerformanceVector.erase(it);
			delete performance;
			continue;
		}
		
		//std::cout << animationName << std::endl;
		if (performance->isFinished(time)) {
			// => Animation is finished - the CharacterPerformance has to be deleted
			entity->getAnimationState(animationName)->setEnabled(false);
			it = characterPerformanceVector.erase(it);
			
			// manual Animations are only played once and therefore should be deleted afterwards
			if (performance->isManualPerformance()) {
				std::cout << "REMOVING ANIMATION "<< performance->getAnimationName() << " FROM SKELETON " << name << std::endl;
				entity->getSkeleton()->removeAnimation(performance->getAnimationName());
				
				entity->getAllAnimationStates()->removeAnimationState(performance->getAnimationName());
				std::cout << "-> DONE [removing anim]"<< std::endl;
				entity->refreshAvailableAnimationState();
				
				Ogre::AnimationStateIterator asIt = entity->getAllAnimationStates()->getAnimationStateIterator();
				while (asIt.hasMoreElements()) {
					Ogre::AnimationState* animState = asIt.getNext();
					std::cout << "----- " << animState->getAnimationName() << std::endl;
				}
			}
			
			delete performance;
			continue;
		} else {
			if (time < performance->getStartTime()) {
				// skip this animation
			} else if (time < performance->getEndTime()) {
				Ogre::AnimationState* animState = entity->getAnimationState(animationName);
				Ogre::Real weight = performance->getIntensity();
				if (time < performance->getStartTime() + performance->getFadeinTime()) {
					//std::cout << "FADE IN " << time << std::endl;
					weight = weight * (time - performance->getStartTime()) / performance->getFadeinTime(); // Fade In
				} else if (time > performance->getEndTime() - performance->getFadeoutTime()) {
					//std::cout << "FADE OUT " << time << " (FadeoutTime=" << performance->getFadeoutTime() << ")" << std::endl;
					weight = weight * (performance->getEndTime() - time) / performance->getFadeoutTime(); // Fade Out
				}
				//std::cout << "ANIMATION_NAME=" << performance->getAnimationName() << std::endl;
				//std::cout << "TIME  =" << time <<   "   START=" << performance->getStartTime() <<     "    EndTime      =" << performance->getEndTime() << std::endl;
				//std::cout << "WEIGHT=" << weight << "   SPEED=" << performance->getSpeedModifier() << "    AnimationTime=" << (time - performance->getStartTime() + performance->getStartOffsetTime()) * performance->getSpeedModifier() << std::endl;
				animState->setWeight(weight);
				animState->setEnabled(true);
				animState->setTimePosition(performance->getStartOffsetTime()  +  (time - performance->getStartTime()) * performance->getSpeedModifier());
			} else {
				// skip this animation
			}

			it++;
		}
	}
	// std::cout << "<<<<<<< END Character.playAnimations >>>>>>>>>>>>>" << std::endl;
}



void Character::dropUnusedAnimations() {
	std::cout << "Character::dropUnusedAnimations() name="<< name << "-BEGIN" << std::endl;
	//	AnimationStates, für welche weder eine Skelett- noch eine Mesh-Animation vorliegt, werden nicht mehr benötigt 
	//	und können daher gelöscht werden.
	Ogre::AnimationStateIterator animStateIt = entity->getAllAnimationStates()->getAnimationStateIterator();
	while (animStateIt.hasMoreElements()) {
		std::string animationName = animStateIt.getNext()->getAnimationName();
		//if (!entity->getSkeleton()->hasAnimation(animationName)
		//&& !facialEntity->getMesh()->hasAnimation(animationName)) {
		if (!entity->getSkeleton()->hasAnimation(animationName)) {
			std::cout << "&&&&&&&&&& "<< name << "  --   REMOVING UNUSED ANIMATION_STATE " << animationName << std::endl;
			entity->getAllAnimationStates()->removeAnimationState(animationName);
			std::cout << "DONE" << std::endl;
		}
	}
	std::cout << "Character::dropUnusedAnimations() name="<< name << "-END" << std::endl;
}

void Character::doEmotionalExpression(Ogre::Real engineTime) {
/*
	BehaviorLibrary* bl = dataManager->getBehaviorLibrary(name);
	for (int i=0; i<EMOTION_END; i++) {
		std::stringstream animationNameStream;
		std::string animationName;
		animationNameStream << "emotion_" << i;
		animationNameStream >> animationName;

		
		// Emotion des Characters auslesen => ergibt das Gewicht für den entsprechenden Gesichtsausdruck
		Ogre::Real weight = dataManager->getEmotion(name, EmotionType(i), engineTime);
		//std::cout << animationName << "=" << weight << std::endl;		
		// Gesichtsausdruck aus BehaviorLibrary des Characters holen und auf den emotionKeyFrame addieren
		FacialExpression* exp = bl->getExpression(EmotionType(i));
		exp->fillKeyFrame(emotionKeyFrameMap[EmotionType(i)], bl->getExpressionLibrary()->getPoseMapping(), weight);
		
		// Ogre zum Aktualisieren des Meshes bringen
		facialEntity->getAnimationState(animationName)->getParent()->_notifyDirty();
	}
*/
}

void Character::doSpeechExpression(Ogre::Real engineTime) {
/*
	BehaviorLibrary* bl = dataManager->getBehaviorLibrary(name);
	
	TimedExpressionMap::iterator it0, it1;
	speechExpressionMap.getCurrentExpressions(it0, it1, engineTime);

	// veraltete Gesichtsausdrücke löschen
	while ((it0!=speechExpressionMap.end()) && (speechExpressionMap.begin() != it0)) {
		speechExpressionMap.erase(speechExpressionMap.begin());
	}
	
	// zwischen den FacialExpression zum Zeitpunkt t0 und t1 linear interpolieren
	Ogre::Real speechVolume = 1; // je lauter, desto höher die Gewichte der Visem-Posen
	if (name=="Herrmann") {
		speechVolume = 1;
	} else if (name=="Quentin") {
		speechVolume = 0.6;
	}
	// TODO: SpeechVolume wird gerade nicht mehr berücksichtigt!	

	
	if (it1 == speechExpressionMap.end()) {
		it0->second->fillKeyFrame(speechKeyFrame, bl->getExpressionLibrary()->getPoseMapping());
	} else {
		Ogre::Real delta = (engineTime - it0->first) / (it1->first - it0->first);
		FacialExpression* fe0 = it0->second->getExpression();
		Ogre::Real weight0 = it0->second->getWeight();
		FacialExpression* fe1 = it1->second->getExpression();
		Ogre::Real weight1 = it1->second->getWeight();
		FacialExpression exp = FacialExpression("currentSpeech");
		ExpressionLibrary* el = bl->getExpressionLibrary();
		StringIntMap* poseMapping = el->getPoseMapping();

		for (StringIntMap::iterator it = poseMapping->begin(); it!=poseMapping->end(); it++) {
			std::string poseName = it->first;
			Ogre::Real value = weight0 * fe0->getPoseWeight(poseName) + delta * (weight1 * fe1->getPoseWeight(poseName) - weight0 * fe0->getPoseWeight(poseName));
			exp.setPoseWeight(poseName, value);
		}
		exp.fillKeyFrame(speechKeyFrame, bl->getExpressionLibrary()->getPoseMapping(), speechVolume);
	}
	facialEntity->getAnimationState("speech")->getParent()->_notifyDirty();
*/
}




void Character::doControlledExpression(Ogre::Real engineTime) {
/*
	BehaviorLibrary* bl = dataManager->getBehaviorLibrary(name);
	
	TimedExpressionMap::iterator it0, it1;
	controlledExpressionMap.getCurrentExpressions(it0, it1, engineTime);
	
	// veraltete Gesichtsausdrücke löschen
	while ((it0!=controlledExpressionMap.end()) && (controlledExpressionMap.begin() != it0)) {
		controlledExpressionMap.erase(controlledExpressionMap.begin());
	}

	// zwischen den FacialExpression zum Zeitpunkt t0 und t1 linear interpolieren
	if (it1 == controlledExpressionMap.end()) {
		it0->second->fillKeyFrame(controlledExpressionKeyFrame, bl->getExpressionLibrary()->getPoseMapping());
	} else {
		Ogre::Real expressionWeight = 1;
	
		Ogre::Real delta = (engineTime - it0->first) / (it1->first - it0->first);
		FacialExpression* fe0 = it0->second->getExpression();
		FacialExpression* fe1 = it1->second->getExpression();
		Ogre::Real weight0 = it0->second->getWeight();
		Ogre::Real weight1 = it1->second->getWeight();
		FacialExpression exp = FacialExpression("controlledExpression");
		
		ExpressionLibrary* el = bl->getExpressionLibrary();		
		StringIntMap* poseMapping = el->getPoseMapping();
		for (StringIntMap::iterator it = poseMapping->begin(); it!=poseMapping->end(); it++) {
			std::string poseName = it->first;
			Ogre::Real value = weight0 * fe0->getPoseWeight(poseName) + delta * (weight1 * fe1->getPoseWeight(poseName) - weight0 * fe0->getPoseWeight(poseName));
			exp.setPoseWeight(poseName, value);
			//std::cout << "!!!! CONTROLLED   POSE=" << poseName << " " << value << std::endl;
		}
		exp.fillKeyFrame(controlledExpressionKeyFrame, bl->getExpressionLibrary()->getPoseMapping(), expressionWeight);
	}
	facialEntity->getAnimationState("controlledExpression")->getParent()->_notifyDirty();
*/
}


void Character::perform() {
	//std::cout << "<<<<<<< Character.perform >>>>>>>>>>>>>" << std::endl;
	//totalTime+= timeSinceLastFrame;
	
	Ogre::Real engineTime = dataManager->getEngineTime();
	
	
	// Skelett-Animation abspielen
	playAnimations();
	
	// === unnötige AnimationStates löschen ===
	dropUnusedAnimations();
	
	
	
	// ======= Gesichtsausdruck aus den Emotionen des Charakters erzeugen ======
	//TODO doEmotionalExpression(engineTime);
	
	// ======= Gesichtsanimation aus Visemen / der sprechende Charakter ======
	//TODO doSpeechExpression(engineTime);
	
	// ======= Gesichtsanimation - kontrollierte Mimik ======
	//TODO doControlledExpression(engineTime);
		
	
	
	
	// AUDIO!!!!
	std::map<Ogre::Real, AudioTrack*>::iterator atIt = audioTrackMap.begin();
	if (atIt != audioTrackMap.end()) {
		if (atIt->first <= engineTime) {
			//if (currentAudioTrack != NULL) {
			std::cout << "PPPPPPPPPPPPP   1" << std::endl;
			AudioTrack* track = atIt->second;
			std::cout << "PPPPPPPPPPPPP   2" << std::endl;
			playAudioTrack(track);
			std::cout << "PPPPPPPPPPPPP   3" << std::endl;
			audioTrackMap.erase(atIt);
			std::cout << "PPPPPPPPPPPPP   4" << std::endl;
			//}
		}
	}
	
	
	
	// "hand-made" Gesichtsanimation abspielen	
	//facialEntity->getAnimationState("manual")->addTime(timeSinceLastFrame);
	
	
	// veraltete KeyFrames löschen (alle 2 Sekunden)
	/*
	if (totalTime > lastFrameDeprecatedCheck + 2) {
		std::cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxx checkin for old KeyFrames ("<< name << " - " << totalTime << " - " << lastFrameDeprecatedCheck << ")" << std::endl;
		lastFrameDeprecatedCheck = totalTime;
		Ogre::Animation* anim = facialEntity->getMesh()->getAnimation("manual");
		Ogre::Animation::VertexTrackIterator it = anim->getVertexTrackIterator();
		while (it.hasMoreElements()) {
			Ogre::VertexAnimationTrack* track = it.getNext();
			int delCounter=0;
			for (int j=0; j < (track->getNumKeyFrames()-1); j++) {
				if (track->getKeyFrame(j+1)->getTime() < totalTime) {
					delCounter++;
				}
			}
			std::cout << "DEL_COUNTER:" << delCounter << std::endl;
			for (int j=0; j<delCounter; j++) {
				std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> REMOVING KEYFRAME 0 (" << name << ") >>>>>>>>>>" << std::endl;
				track->removeKeyFrame(j);
			}
		
		}
	}
	*/
	//std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<" << name << "  Time=" << totalTime << "  Joy=" << (dataManager->getEmotion(name, CharacterData::EMOTION_JOY, totalTime)) << std::endl;
}






/** Der y-Anteil der Direction wird entfernt, da sich der Robot nur auf der Ebene bewegen können soll. **/
void Character::setDirection(const Ogre::Vector3 direction) {
	//sceneNode->setDirection(direction.x, 0., direction.z, Ogre::Node::TS_PARENT);
	sceneNode->setDirection(direction.x, direction.y, direction.z, Ogre::Node::TS_PARENT);
}




void Character::rotate(const Ogre::Vector3 dir, const Ogre::Real timeSinceLastFrame) {
	//std::cout << "Character->rotate(" << dir << ", " << timeSinceLastFrame << ")" << std::endl;
	//sceneNode->setDirection(dir, Ogre::Node::TS_LOCAL, Ogre::Vector3::UNIT_X);
	
	Ogre::Quaternion q = sceneNode->getWorldOrientation().xAxis().getRotationTo(dir);

	float degrees = q.getYaw().valueDegrees();
	if (abs(degrees) > 90*timeSinceLastFrame) {
		degrees = 90*timeSinceLastFrame;
		if (q.getYaw().valueDegrees()<0) {
			degrees *= -1;
		}
	}
	//std::cout << "needed Rotation" << q.getYaw().valueDegrees() << "    performed Rotation" << degrees<< std::endl;
	
	sceneNode->rotate(Ogre::Vector3::UNIT_Y, Ogre::Degree(degrees), Ogre::Node::TS_LOCAL);
}


} // end of namespace
