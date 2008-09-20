/*
 *  Character.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 01.02.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef CHARACTER_H
#define CHARACTER_H

// std includes
#include <deque>
#include <map>
#include <string>

// dependency includes
#include <OpenAL/alc.h>
//#include <OpenAL/alut.h>
#ifdef OSX
    #include <Ogre/Ogre.h>
#else
    #include <Ogre.h>
#endif

// project includes
#include "AudioTrack.h"
#include "CharacterExpression.h"
#include "CharacterPerformanceVector.h"
#include "EmotionTypes.h"
#include "FKPerformanceVector.h"
#include "TimedExpressionMap.h"

namespace Charanis {

class DataManager;
class CharacterPerformance;
class FKPerformance;


/**
 * \brief Repräsentation eines Charakters in der Ausgabe-Komponente.
 *
 * Für jeden Charakter in der Szene verwaltet der RenderingLayer ein eigenes Character-Objekt. Der Zugriff
 *
 * Ein solches Character-Objekt repr\"asentiert einen Charakter innerhalb der Szene. Es beinhaltet alle Informationen,
 * die zum Rendern des Charakters notwendig sind: das 3D-Modell, Informationen zu dessen Position, sowie alle
 * Bewegungskommandos, die der RenderingLayer für diesen Charakter empfangen hat. Ein Character-Objekt
 * ist also selber für die Verwaltung und Steuerung aller den zugehörigen Charakter betreffenden Animationen 
 * zuständig.
 *			
 * Vor dem Zeichnen eines jeden Frames ruft der RenderingLayer auf dem Character-Objekt die 
 * Methode perform() auf. Diese wandelt nun die Bewegungsanweisungen an den Charakter in konkrete 
 * Animationen um und spielt dazu die synthetisierte Sprache ab.
 */
class Character {
	private:
		std::string name;
		Ogre::SceneManager* sceneManager;
		
		Ogre::SceneNode* sceneNode;
		Ogre::Entity* entity;

		//Ogre::SceneNode* facialNode;
		Ogre::Entity* leftEyeEntity;
		Ogre::Entity* rightEyeEntity;
		Ogre::Entity* facialEntity;
		
		DataManager* dataManager;
		
		// Skelett-Animation
		CharacterPerformanceVector characterPerformanceVector;
		//FKPerformanceVector fkPerformanceVector;

		// Gesichtsanimation - Emotionen
		std::map<EmotionType, Ogre::VertexPoseKeyFrame*> emotionKeyFrameMap;
		
		// Gesichtsanimation - Sprache / Viseme
		TimedExpressionMap speechExpressionMap; // Key: Zeitpunkt,    Value: Gesichtsausdruck.    es wird linear dazwischen interpoliert
		Ogre::VertexPoseKeyFrame* speechKeyFrame;

		// Gesichtsanimation - kontrollierte Mimik
		TimedExpressionMap controlledExpressionMap;
		Ogre::VertexPoseKeyFrame* controlledExpressionKeyFrame;

		//Ogre::Real totalTime;
		//Ogre::Real lastFrameDeprecatedCheck;
		
		const Ogre::Real DISTANCE_TOLERANCE;
		std::deque<Ogre::Vector3> waypointQueue;
		
		//static const int NUM_BUFFERS=2;
		ALuint audioSource[1];
		//ALuint buffers[NUM_BUFFERS];
		
		AudioTrack* currentAudioTrack;
		std::map<Ogre::Real, AudioTrack*> audioTrackMap;
		
		
		// Helper methods for initialization
		void addEyes(const std::string& meshName);
		void createFacialAnimations(Ogre::MeshPtr& facialMesh);
		
		void printBones();
		void printMeshes();
		void printMeshAnimations();
		void printAnimationStates();
	public:
		Character(Ogre::SceneManager* sceneManager, Ogre::SceneNode* parentNode, std::string meshName, DataManager* dm, std::string name, Ogre::Real scale=1);
		~Character();
		
		void importSAMLFile(std::string fileName);
		void importFEMLFile(std::string fileName);
		
		std::string getName();
		
		void setPosition(const Ogre::Vector3 pos);
		Ogre::Vector3 getPosition();
		
		
		void addFKPerformance(FKPerformance* performance);
		void addFKPerformances(FKPerformanceVector* performanceVec);
		
		void addPerformance(CharacterPerformance* performance);
		void addPerformances(CharacterPerformanceVector* performanceVec);
		
		void addSpeechExpression(CharacterExpression* exp);
		void addSpeechExpressions(TimedExpressionMap* expressionMap);
		
		
		void addControlledExpression(CharacterExpression* exp);
		void addControlledExpressions(TimedExpressionMap* expressionMap);
		
		void playAudioTrack(Charanis::AudioTrack* track);
		void addAudioTrack(Charanis::AudioTrack* track);
		
		void playAnimations();
		void dropUnusedAnimations();
		void doEmotionalExpression(Ogre::Real engineTime);
		void doSpeechExpression(Ogre::Real engineTime);
		void doControlledExpression(Ogre::Real engineTime);
		
		void perform();
		
		void setDirection(const Ogre::Vector3 direction);
		void rotate(const Ogre::Vector3 dir, const Ogre::Real timeSinceLastFrame);
};

} // end of namespace

#endif
