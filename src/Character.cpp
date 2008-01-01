/*
 *  Character.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 01.02.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "Character.h"


namespace Charanis {

Character::Character(Ogre::SceneManager* sceneManager, Ogre::SceneNode* parentNode, std::string meshName, DataManager* dm, std::string name, Ogre::Real scale)
		: DISTANCE_TOLERANCE(1) {
	std::cout << "===== Constructor Character ("<< name << ") ====" << std::endl;
	this->name = name;
	this->sceneManager = sceneManager;
	this->dataManager = dm;
	
	facialNode = NULL;
	facialEntity = NULL;
	//dataManager->addCharacter(name); // this ist now done by the EngineManager
	
	
	BehaviorLibrary* bl = dataManager->getBehaviorLibrary(name);
	
	// create the entity
	entity = sceneManager->createEntity(name, meshName);
	
	
	
	
	sceneNode = parentNode->createChildSceneNode(name+"Node");
	sceneNode->attachObject(entity);
	sceneNode->setScale(scale, scale, scale);
	

	// set some parameters of the entity
	//entity->setDisplaySkeleton(true);
	//sceneNode->showBoundingBox(true);
	entity->setCastShadows(true);
	//entity->setCastShadows(false);
	entity->getSkeleton()->setBlendMode(Ogre::ANIMBLEND_CUMULATIVE);
	
	
	/*========== AUGEN EINFUEGEN ===============*/
	//entity->getSkeleton()->getBone("Joint12")->createChild(18, Ogre::Vector3(10, 130, 0));
	//entity->getSkeleton()->getBone("Joint12")->createChild(19, Ogre::Vector3(-10, 130, 0));
	
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
	} else {
		leftEyeEntity = NULL;
		rightEyeEntity = NULL;
	}
	
	
	
	
	std::cout << "Skeleton of Character " << name << ":" << std::endl;
	Ogre::Skeleton::BoneIterator boneIt = entity->getSkeleton()->getBoneIterator();
	while (boneIt.hasMoreElements()) {
		Ogre::Bone* bone = boneIt.getNext();
		std::cout << "----- " << bone->getName() << " ("<< bone->getHandle() << ")" << std::endl;
	}
	
	std::cout << "Meshes of Character " << name << ":" << std::endl;
	Ogre::Mesh::SubMeshIterator subMeshIt = entity->getMesh()->getSubMeshIterator();
	while (subMeshIt.hasMoreElements()) {
		Ogre::SubMesh* subMesh = subMeshIt.getNext();
		std::cout << "----- " << subMesh->getMaterialName() << std::endl;
	}
	
	
	std::cout << "Available Animations for Character " << name << ":" << std::endl;
	Ogre::AnimationStateIterator it = entity->getAllAnimationStates()->getAnimationStateIterator();
	while (it.hasMoreElements()) {
		Ogre::AnimationState* animState = it.getNext();
		std::cout << "----- " << animState->getAnimationName() << std::endl;
		bl->addBodyAnimation(new BodyAnimation(animState->getAnimationName()));
	}
	
	bl->printBodyAnimations();
	
	
	
	
	
	
	ExpressionLibrary* expressionLibrary = bl->getExpressionLibrary();
	StringIntMap* poseMapping = expressionLibrary->getPoseMapping();
	
	std::string faceMeshName = name+"Face.mesh";
	
	Ogre::MeshPtr origMesh = Ogre::MeshManager::getSingleton().load("facial.mesh", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	Ogre::MeshPtr newMesh = origMesh->clone(faceMeshName);
	
	for (int i=0; i<newMesh->getPoseCount(); i++) {
		Ogre::Pose* pose = newMesh->getPose(i);
		std::cout << "Adding Pose " << pose->getName() << " at index " << i << std::endl;
		expressionLibrary->addPoseMapping(pose->getName(), i);
	}
	
	
	
	// some Random Test....
	/*
	boost::mt19937 rng;
	rng.seed(static_cast<unsigned int>(std::time(0)));
	boost::uniform_int<> six(6,10);
	boost::uniform_int<> hundred(0,100);
	
	boost::variate_generator<boost::mt19937, boost::uniform_int<> > die(rng, six);
	boost::variate_generator<boost::mt19937, boost::uniform_int<> > d100(rng, hundred);
	
	
	// END Random Test
	
	int au1 = die();
	int au2 = die();
	int au3 = die();
	
	
	Ogre::Animation* anim = newMesh->createAnimation("manual", 30);
	Ogre::VertexAnimationTrack* track = anim->createVertexTrack(4, Ogre::VAT_POSE);
	
	Ogre::VertexPoseKeyFrame* kf = track->createVertexPoseKeyFrame(0);
	kf->updatePoseReference(au1,0);
	kf->updatePoseReference(au2,0);
	kf->updatePoseReference(au3,1);
	kf = track->createVertexPoseKeyFrame(2);
	kf->updatePoseReference(au1,1);
	kf->updatePoseReference(au2,0);
	kf->updatePoseReference(au3,0);
	kf = track->createVertexPoseKeyFrame(5);
	kf->updatePoseReference(au1,0);
	kf->updatePoseReference(au2,1);
	kf->updatePoseReference(au3,0);
	kf = track->createVertexPoseKeyFrame(8);
	kf->updatePoseReference(au1,1);
	kf = track->createVertexPoseKeyFrame(9);
	kf->updatePoseReference(au1,0);
	kf = track->createVertexPoseKeyFrame(10);
	kf->updatePoseReference(au1,1);
	kf = track->createVertexPoseKeyFrame(12);
	kf->updatePoseReference(au1,0);
	kf = track->createVertexPoseKeyFrame(14);
	kf->updatePoseReference(au1,1);
	kf = track->createVertexPoseKeyFrame(16);
	kf->updatePoseReference(au1,0);
	kf = track->createVertexPoseKeyFrame(18);
	kf->updatePoseReference(au1,1);
	kf = track->createVertexPoseKeyFrame(20);
	kf->updatePoseReference(au1,0);
	kf = track->createVertexPoseKeyFrame(22);
	kf->updatePoseReference(au1,1);
	kf = track->createVertexPoseKeyFrame(24);
	kf->updatePoseReference(au1,0);
	kf = track->createVertexPoseKeyFrame(26);
	kf->updatePoseReference(au1,1);
	*/


	
	//==== Emotionen-Animationen und die KeyFrames anlegen
	for (int i=0; i<EMOTION_END; i++) {
		std::stringstream animationNameStream;
		std::string animationName;
		animationNameStream << "emotion_" << i;
		animationNameStream >> animationName;
		
		Ogre::Animation* emotionAnim = newMesh->createAnimation(animationName, 0);
		Ogre::VertexAnimationTrack* emotionTrack = emotionAnim->createVertexTrack(4, Ogre::VAT_POSE);
		emotionKeyFrameMap[EmotionType(i)] = emotionTrack->createVertexPoseKeyFrame(0);
		
		for (StringIntMap::iterator it = poseMapping->begin(); it!=poseMapping->end(); it++) {
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
	

	// Sage: "Hallo"
	/*
	if (name!="Robbie") {
		speechExpressionMap[4] = bl->getExpression("neutral");
		speechExpressionMap[4.3] = bl->getExpression("VISEME_A");
		speechExpressionMap[4.6] = bl->getExpression("VISEME_L");
		speechExpressionMap[4.9] = bl->getExpression("VISEME_O");
		speechExpressionMap[5.5] = bl->getExpression("neutral");
		
		speechExpressionMap[7] = bl->getExpression("neutral");
		speechExpressionMap[7.3] = bl->getExpression("VISEME_A");
		speechExpressionMap[7.6] = bl->getExpression("VISEME_L");
		speechExpressionMap[7.9] = bl->getExpression("VISEME_O");
		speechExpressionMap[8.5] = bl->getExpression("neutral");
	 
		
		
		speechExpressionMap[10] = bl->getExpression("neutral");
		speechExpressionMap[10.3] = bl->getExpression("VISEME_A");
		speechExpressionMap[10.6] = bl->getExpression("VISEME_L");
		speechExpressionMap[10.9] = bl->getExpression("VISEME_O");
		speechExpressionMap[11.5] = bl->getExpression("neutral");


		speechExpressionMap[15] = bl->getExpression("neutral");
		speechExpressionMap[15.3] = bl->getExpression("VISEME_A");
		speechExpressionMap[15.6] = bl->getExpression("VISEME_L");
		speechExpressionMap[15.9] = bl->getExpression("VISEME_O");
		speechExpressionMap[16.5] = bl->getExpression("neutral");
	}
	*/
	facialEntity = sceneManager->createEntity(name+"Face", faceMeshName);
	facialEntity->setCastShadows(false);
	
	/*
	if (name=="Robbie") {
		facialEntity->getAnimationState("manual")->setEnabled(true);
	} else {
		facialEntity->getAnimationState("manual")->setEnabled(false);
	}
	facialEntity->getAnimationState("manual")->setLoop(true);
	facialEntity->getAnimationState("manual")->setTimePosition(0);
	*/
	
	
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

	
	
	if (meshName == "robot.mesh") {
		Ogre::TagPoint* facialTagPoint = entity->attachObjectToBone("Joint12", facialEntity);
		facialTagPoint->setScale(0.3, 0.3, 0.3);
		facialTagPoint->rotate(Ogre::Vector3(0,1,0), Ogre::Degree(90));
		facialTagPoint->translate(5, -10, 0);
	} else {
		facialNode = sceneManager->getRootSceneNode()->createChildSceneNode(name+"FaceNode");
		facialNode->setScale(0.2, 0.2, 0.2);
		facialNode->attachObject(facialEntity);
	}

	
	
	
	
	
	
	
		
	
	
	
	

	
	/*
	Ogre::Skeleton::BoneIterator it = entity->getSkeleton()->getBoneIterator(); 
	while (it.hasMoreElements()) {
		Ogre::Bone* bone = it.getNext();
		std::cout << "BONE: " << bone->getName() << " (" << bone->getHandle() << ")" << std::endl;
	}
	*/
	
	/*
	// Create and Compose Animations
	Ogre::Animation* anim;
	
	Ogre::NodeAnimationTrack* animTrack;
	Ogre::TransformKeyFrame* kf;
	
	try {
		entity->getSkeleton()->getAnimation("BendKnee");
		std::cout << "!!!!!!!!!!! ANIMATION BendKnee ALREADY EXISTS" << std::endl;
	} catch (...) {
		std::cout << "!!!!!!!!!!! CREATING ANIMATION BendKnee" << std::endl;
		anim = entity->getSkeleton()->createAnimation("BendKnee", 1);
		animTrack = anim->createNodeTrack(entity->getSkeleton()->getBone("Joint7")->getHandle(), entity->getSkeleton()->getBone("Joint7"));
		kf = animTrack->createNodeKeyFrame(0);
		kf->setRotation(Ogre::Quaternion(1, 0, 0, 0));
		kf = animTrack->createNodeKeyFrame(0.5);
		kf->setRotation(Ogre::Quaternion(1, 0, 0, -0.5));
		kf = animTrack->createNodeKeyFrame(1);
		kf->setRotation(Ogre::Quaternion(1, 0, 0, 0));
	}
	
	
	try {
		entity->getSkeleton()->getAnimation("LiftLeg");
		std::cout << "!!!!!!!!!!! ANIMATION LiftLeg ALREADY EXISTS" << std::endl;
	} catch (...) {
		std::cout << "!!!!!!!!!!! CREATING ANIMATION LiftLeg" << std::endl;
		anim = entity->getSkeleton()->createAnimation("LiftLeg", 1.5);
		animTrack = anim->createNodeTrack(entity->getSkeleton()->getBone("Joint6")->getHandle(), entity->getSkeleton()->getBone("Joint6"));
		kf = animTrack->createNodeKeyFrame(0.5);
		kf->setRotation(Ogre::Quaternion(1, 0, 0, 0));
		kf = animTrack->createNodeKeyFrame(1);
		kf->setRotation(Ogre::Quaternion(1, 0, 0, 0.5));
		kf->setScale(Ogre::Vector3(2, 1, 1));
		kf = animTrack->createNodeKeyFrame(1.5);
		kf->setRotation(Ogre::Quaternion(1, 0, 0, 0));
	}
	
	try {
		entity->getSkeleton()->getAnimation("LiftLeg_combined");
		std::cout << "!!!!!!!!!!! ANIMATION LiftLeg_combined ALREADY EXISTS" << std::endl;
	} catch (...) {
		std::cout << "!!!!!!!!!!! CREATING ANIMATION LiftLeg_combined" << std::endl;
		std::vector<Ogre::Animation*> animVec;
		animVec.push_back(entity->getSkeleton()->getAnimation("BendKnee"));
		animVec.push_back(entity->getSkeleton()->getAnimation("LiftLeg"));
		composeAnimations("LiftLeg_combined", animVec);
	}
	*/
	

	
	
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
	
	
	std::string filename = "../../../../CLEAN_UP/sound_engine.wav";
	if (name=="Robbie") {
		filename = "../../../../CLEAN_UP/sound_electric.wav";
	}
	playAudioTrack(new AudioTrack(filename, 0));
	
	
	
	
	// EXPORTING THE NEW SKELETON
	/*
	if (name=="Robbie") {
		Ogre::SkeletonSerializer skeletonSerializer = Ogre::SkeletonSerializer();
		skeletonSerializer.exportSkeleton(entity->getSkeleton(), "complete_model.skeleton");
	
		Ogre::Entity* leye = sceneManager->getEntity(name+"_LEYE");
		Ogre::Mesh::SubMeshIterator it = leye->getMesh()->getSubMeshIterator();
		int itNo = 1;
		while (it.hasMoreElements()) {
		//Ogre::Mesh::SubMeshNameMap nameMap = leye->getMesh()->getSubMeshNameMap();
		//for (Ogre::Mesh::SubMeshNameMap::iterator it = nameMap.begin(); it!=nameMap.end(); it++){
			//std::string subMeshName = it->first;
			//Ogre::SubMesh* orig = leye->getMesh()->getSubMesh(it->second);
			std::string subMeshName;
			std::stringstream subMeshNameStream;
			subMeshNameStream << "l_" << itNo++;
			subMeshNameStream >> subMeshName;
			Ogre::SubMesh* orig = it.getNext();
			
			//Ogre::Vector3* bonePos = entity->getSkeleton()->getBone("l_eyeball_joint")->_getDerivedPosition();
			
			Ogre::SubMesh* newSubMesh = entity->getMesh()->createSubMesh("l_"+subMeshName);
			newSubMesh->useSharedVertices = false;
			newSubMesh->vertexData = orig->vertexData->clone();
			newSubMesh->indexData = orig->indexData->clone();
			newSubMesh->setMaterialName(orig->getMaterialName());
			
			unsigned short boneHandle = entity->getSkeleton()->getBone("l_eyeball_joint")->getHandle();
			int vertexNo = newSubMesh->vertexData->vertexStart;
			int maxVertexNo = vertexNo + newSubMesh->vertexData->vertexCount;
			while (vertexNo < maxVertexNo) {
				Ogre::VertexBoneAssignment vba;
				vba.vertexIndex = vertexNo++;
				vba.boneIndex = boneHandle;
				vba.weight = 1;
				newSubMesh->addBoneAssignment(vba);
			}
		}
		
		
		//std::cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX    LISTING THE SUB_MESHES" << std::endl;
		//nameMap = entity->getMesh()->getSubMeshNameMap();
		//for (Ogre::Mesh::SubMeshNameMap::iterator it = nameMap.begin(); it!=nameMap.end(); it++){
		//	std::cout << "---------" << it->first << std::endl;
		//}
		//std::cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX    DONE" << std::endl;
		
		
		Ogre::MeshSerializer meshSerializer = Ogre::MeshSerializer();
		meshSerializer.exportMesh(entity->getMesh().get(), "complete_model.mesh");
		
		
	}
	*/
	

	
	//totalTime = 0;
	//lastFrameDeprecatedCheck = 0;
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
		entity->detachObjectFromBone(facialEntity->getName());
		
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
	std::cout << "Character::playAudioTrack(..)   ---  A" << std::endl;
	alSourceStop(audioSource[0]);
	std::cout << "Character::playAudioTrack(AudioTrack* track)   -   alSourceStop(audioSource[0]);" << alGetError()  << std::endl;
	

	std::cout << "Attaching Source..." << std::endl;
	
	alSourcei(audioSource[0], AL_BUFFER, track->getBuffer());
	if ((error = alGetError()) != AL_NO_ERROR) {
		std::cout << "alSourcei : " <<  error << std::endl;
		exit(0);
	}
	
	std::cout << "Character::playAudioTrack(..)   ---  B" << std::endl;
	if (currentAudioTrack != NULL) {
		//alSourceUnqueueBuffers(audioSource[0], 1, currentAudioTrack->getBuffer());
		delete currentAudioTrack;
	}
	currentAudioTrack = track;
	
	
	std::cout << "Character::playAudioTrack(..)   ---  C" << std::endl;
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
	if (facialNode != NULL) {
		facialNode->setPosition(pos[0], pos[1]+80, pos[2]);
	}
	
	
	float vec[3];
	vec[0] = pos.x;
	vec[1] = entity->getWorldBoundingBox().getMaximum().y; //pos.y;
	vec[2] = pos.z;
	alSourcefv(audioSource[0], AL_POSITION, vec);
}




Ogre::Vector3 Character::getPosition() {
	return sceneNode->getPosition();
}






void Character::composeAnimations(std::string newAnimationName, Ogre::Animation* anim1, Ogre::Animation* anim2) {
	Ogre::Real length = std::max(anim1->getLength(), anim2->getLength());
	Ogre::Animation* combinedAnim = entity->getSkeleton()->createAnimation(newAnimationName, length);
	
	Ogre::Skeleton::BoneIterator boneIt = entity->getSkeleton()->getBoneIterator(); 
	while (boneIt.hasMoreElements()) {
		Ogre::Bone* bone = boneIt.getNext();
		
		Ogre::NodeAnimationTrack* animTrack1 = NULL;
		Ogre::NodeAnimationTrack* animTrack2 = NULL;
		try {
			animTrack1 = anim1->getNodeTrack(bone->getHandle());
		} catch (...) {
			// nothing to do
		}
		
		try {
			animTrack2 = anim2->getNodeTrack(bone->getHandle());
		} catch (...) {
			// nothing to do
		}
		
		
		if ((animTrack1 != NULL) && (animTrack2 != NULL)) {
			Ogre::NodeAnimationTrack* combinedAnimTrack = combinedAnim->createNodeTrack(bone->getHandle());
			
			if (animTrack1 != NULL) {
				for (int i=0; i < animTrack1->getNumKeyFrames(); i++) {
					Ogre::TransformKeyFrame* kf1 = animTrack1->getNodeKeyFrame(i);
					Ogre::Real time = kf1->getTime();
					Ogre::TransformKeyFrame* combinedKf = combinedAnimTrack->createNodeKeyFrame(time);
					
					if (animTrack2 != NULL) {
						Ogre::TransformKeyFrame* kf2;
						animTrack2->getInterpolatedKeyFrame(time, kf2);
					
						combinedKf->setRotation(kf1->getRotation() * kf2->getRotation());
						combinedKf->setTranslate(kf1->getTranslate() + kf2->getTranslate());
						combinedKf->setScale(kf1->getScale() * kf2->getScale());
					} else {
						combinedKf->setRotation(kf1->getRotation());
						combinedKf->setTranslate(kf1->getTranslate());
						combinedKf->setScale(kf1->getScale());
					}
				}
			}
			if (animTrack2 != NULL) {
				for (int i=0; i < animTrack2->getNumKeyFrames(); i++) {
					Ogre::TransformKeyFrame* kf2 = animTrack2->getNodeKeyFrame(i);
					Ogre::Real time = kf2->getTime();
					Ogre::TransformKeyFrame* combinedKf = combinedAnimTrack->createNodeKeyFrame(time);
					
					if (animTrack1 != NULL) {
						Ogre::TransformKeyFrame* kf1;
						animTrack1->getInterpolatedKeyFrame(time, kf1);
					
						combinedKf->setRotation(kf1->getRotation() * kf2->getRotation());
						combinedKf->setTranslate(kf1->getTranslate() + kf2->getTranslate());
						combinedKf->setScale(kf1->getScale() * kf2->getScale());
					} else {
						combinedKf->setRotation(kf2->getRotation());
						combinedKf->setTranslate(kf2->getTranslate());
						combinedKf->setScale(kf2->getScale());
					}
				}
			}
		}
	}
	entity->refreshAvailableAnimationState();
}



void Character::composeAnimations(std::string newAnimationName, std::vector<Ogre::Animation*> animVec) {
	Ogre::Real length = 0;
	for (int i=0; i<animVec.size(); i++) {
		length = std::max(length, animVec[i]->getLength());
	}
	
	Ogre::Animation* combinedAnim = entity->getSkeleton()->createAnimation(newAnimationName, length);
	
	std::cout << "Animation " << newAnimationName << " created" << std::endl;
	
	Ogre::Skeleton::BoneIterator boneIt = entity->getSkeleton()->getBoneIterator(); 
	while (boneIt.hasMoreElements()) {
		Ogre::Bone* bone = boneIt.getNext();
		
		// Create all Keyframes
		for (int i=0; i<animVec.size(); i++) {
			try {
				Ogre::NodeAnimationTrack* animTrack= animVec[i]->getNodeTrack(bone->getHandle());
				
				Ogre::NodeAnimationTrack* combinedAnimTrack = NULL;
				try {
					combinedAnimTrack = combinedAnim->getNodeTrack(bone->getHandle());
				} catch (...) {
					combinedAnimTrack = combinedAnim->createNodeTrack(bone->getHandle());
				}
				
				
				for (int j=0; j<animTrack->getNumKeyFrames(); j++) {
					Ogre::TransformKeyFrame* kf = animTrack->getNodeKeyFrame(j);
					Ogre::Real time = kf->getTime();
					
					//Ogre::TransformKeyFrame* combinedKf = 
					combinedAnimTrack->createNodeKeyFrame(time);
				}
			} catch (...) {
				// nothing to do
			}
		}
		
		try {
			Ogre::NodeAnimationTrack* combinedAnimTrack = combinedAnim->getNodeTrack(bone->getHandle());
			for (int j=0; j<combinedAnimTrack->getNumKeyFrames(); j++) {
				Ogre::TransformKeyFrame* combinedKf = combinedAnimTrack->getNodeKeyFrame(j);
				for (int k=0; k<animVec.size(); k++) {
					try {
						//Ogre::TransformKeyFrame* kf;
						Ogre::TransformKeyFrame* kf = new Ogre::TransformKeyFrame(NULL, 0);
						Ogre::NodeAnimationTrack* track = animVec[k]->getNodeTrack(bone->getHandle());
						
						track->getInterpolatedKeyFrame(combinedKf->getTime(), kf);
						combinedKf->setRotation(combinedKf->getRotation() * ((Ogre::TransformKeyFrame*) kf)->getRotation());
						combinedKf->setTranslate(combinedKf->getTranslate() + ((Ogre::TransformKeyFrame*) kf)->getTranslate());
						combinedKf->setScale(combinedKf->getScale() * ((Ogre::TransformKeyFrame*) kf)->getScale());
					} catch (...) {
						// nothing to do
					}
				}
			}
		} catch (...) {
			// nothing to do
		}
	}
	entity->refreshAvailableAnimationState();
}



void Character::addFKPerformance(FKPerformance* performance) {
	std::cout << "addFKPerformance - BEGIN" << std::endl;
	
	
	Ogre::Animation* anim = performance->createOgreAnimation(entity);
	entity->refreshAvailableAnimationState();
	
	//entity->getAnimationState(anim->getName())->setEnabled(true);
	//CharacterPerformance* cp = new CharacterPerformance(name, "MANUAL_TEST_ANIMATION", 0, performance->getLength());
	//cp->setManualPerformance(true);
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


/*
void Character::addSpeechExpression(Ogre::Real time, FacialExpression* exp) {
	speechExpressionMap[time] = exp;
}
*/
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
					//Ogre::AnimationState* animState = asIt.getNext();
					//if (!entity->getSkeleton->hasAnimation(animState->getAnimationName()) && !entity->)
					
					
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






void Character::perform() {
	//std::cout << "<<<<<<< Character.perform >>>>>>>>>>>>>" << std::endl;
	//totalTime+= timeSinceLastFrame;
	
	Ogre::Real engineTime = dataManager->getEngineTime();
	
	
	// Skelett-Animation abspielen
	playAnimations();
	
	
	// === unnötige AnimationStates löschen ===
	//	AnimationStates, für welche weder eine Skelett- noch eine Mesh-Animation vorliegt, werden nicht mehr benötigt 
	//	und können daher gelöscht werden.
	Ogre::AnimationStateIterator animStateIt = entity->getAllAnimationStates()->getAnimationStateIterator();
	while (animStateIt.hasMoreElements()) {
		std::string animationName = animStateIt.getNext()->getAnimationName();
		if (!entity->getSkeleton()->hasAnimation(animationName)
		&& !facialEntity->getMesh()->hasAnimation(animationName)) {
			std::cout << "&&&&&&&&&& "<< name << "  --   REMOVING UNUSED ANIMATION_STATE " << animationName << std::endl;
			entity->getAllAnimationStates()->removeAnimationState(animationName);
			std::cout << "DONE" << std::endl;
		}
	}
	
	
	
	// ======= Gesichtsausdruck aus den Emotionen des Charakters erzeugen ======
	//std::cout << name << " " << totalTime << std::endl;
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

	
	
	// ======= Gesichtsanimation aus Visemen / der sprechende Charakter ======
	TimedExpressionMap::iterator it = speechExpressionMap.begin();
	Ogre::Real t0=0;
	Ogre::Real t1=0;
	// gehe bis zum ersten Zeitpunkt größer als der aktuellen Zeit
	while (it!=speechExpressionMap.end()) {
		if (it->first > engineTime) {
			t1 = it->first;
			break;
		} else {
			t0 = it->first;
		}
		
		it++;
	}
	
	if (t1==0) {
		t1=t0;
	}
	
	// veraltete Viseme aus der map löschen
	while ((t0>0) && (speechExpressionMap.begin()->first < t0)) {
		//std::cout << "REMOVING Expression " << speechExpressionMap.begin()->first << "   (curTime="<< totalTime <<")" << std::endl;
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
	
	if (t1 == t0) {
		speechExpressionMap[t0]->fillKeyFrame(speechKeyFrame, bl->getExpressionLibrary()->getPoseMapping());
	} else {
		Ogre::Real delta = (engineTime - t0) / (t1 - t0);
		FacialExpression* fe0 = speechExpressionMap[t0]->getExpression();
		Ogre::Real weight0 = speechExpressionMap[t0]->getWeight();
		FacialExpression* fe1 = speechExpressionMap[t1]->getExpression();
		Ogre::Real weight1 = speechExpressionMap[t1]->getWeight();
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

	
	
	// ======= Gesichtsanimation - kontrollierte Mimik ======
	it = controlledExpressionMap.begin();
	t0=0;
	t1=0;
	// gehe bis zum ersten Zeitpunkt größer als der aktuellen Zeit
	while (it!=controlledExpressionMap.end()) {
		if (it->first > engineTime) {
			t1 = it->first;
			break;
		} else {
			t0 = it->first;
		}
		
		it++;
	}
	
	if (t1==0) {
		t1=t0;
	}
	
	// veraltete Gesichtsausdrücke löschen
	while ((t0>0) && (controlledExpressionMap.begin()->first < t0)) {
		controlledExpressionMap.erase(controlledExpressionMap.begin());
	}
	
	
	// zwischen den FacialExpression zum Zeitpunkt t0 und t1 linear interpolieren
	if (t1 == t0) {
		controlledExpressionMap[t0]->fillKeyFrame(controlledExpressionKeyFrame, bl->getExpressionLibrary()->getPoseMapping());
	} else {
		Ogre::Real expressionWeight = 1;
	
		Ogre::Real delta = (engineTime - t0) / (t1 - t0);
		FacialExpression* fe0 = controlledExpressionMap[t0]->getExpression();
		FacialExpression* fe1 = controlledExpressionMap[t1]->getExpression();
		Ogre::Real weight0 = controlledExpressionMap[t0]->getWeight();
		Ogre::Real weight1 = controlledExpressionMap[t1]->getWeight();
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


void Character::addWayPoint(const Ogre::Vector3 pos) {
	waypointQueue.push_back(pos);
}




Ogre::Vector3 Character::getNextWayPoint() {
	return waypointQueue.front();
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






void Character::walkPath(const Ogre::Real timeSinceLastFrame) {
	if (waypointQueue.empty()) {
		return; // No Waypoints in Queue => nothing to do
	}
	
	Ogre::Vector3 waypoint = waypointQueue.front();
	Ogre::Vector3 curPos = sceneNode->getWorldPosition();
	
	if ( (waypoint - curPos).length() < DISTANCE_TOLERANCE ) {
		std::cout << "Waypoint reached!!!" << std::endl;
		// bereits am wayPoint angekommen
		// => aktuellen WayPoint aus der Schlange entfernen und nochmal walkPath aufrufen() - also zum nächsten WayPoint laufen
		waypointQueue.pop_front();
		return walkPath(timeSinceLastFrame);
	} else {
		// noch was zu laufen
		
		// in die richtige Richtung drehen
		Ogre::Vector3 dir = waypoint - curPos;
		//std::cout << sceneNode->getWorldOrientation().xAxis() << "->" << dir << std::endl;
		
		
		//if (! dir.directionEquals(sceneNode->getWorldOrientation().xAxis(), Ogre::Degree(5))) {
		if (abs(sceneNode->getWorldOrientation().xAxis().getRotationTo(dir).getYaw().valueDegrees()) >= 2) {
			return rotate(dir, timeSinceLastFrame);
		}
		sceneNode->setDirection(dir, Ogre::Node::TS_PARENT, Ogre::Vector3::UNIT_X);
		
		// laufen
		Ogre::Real distance = 50 * timeSinceLastFrame;
		if (distance > dir.length()) // soll nicht zu weit laufen
			distance = dir.length();
		
		sceneNode->translate(Ogre::Vector3(distance, 0, 0), Ogre::Node::TS_LOCAL);
		Ogre::AnimationState *animState = entity->getAnimationState("Walk");
		if (!animState->getEnabled()) {
			entity->getSkeleton()->reset();
			animState->setEnabled(true);
		} else {
			animState->addTime(timeSinceLastFrame);
		}
	}
}

} // end of namespace