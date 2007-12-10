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

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>

#include <boost/random.hpp>
#include <boost/random/linear_congruential.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>

#include "OpenAL/alc.h"
//#include "OpenAL/alut.h"

#include "SDL/SDL.h"

#include "Ogre/Ogre.h"
#include "Ogre/OgreTagPoint.h"
#include "Ogre/OgreSkeletonSerializer.h"

#include "EmotionTypes.h"
#include "DataManager.h"
#include "CharacterPerformance.h"
#include "CharacterPerformanceVector.h"
#include "CharacterPerformanceMap.h"
#include "FKPerformance.h"
#include "FKPerformanceVector.h"

#include "FacialExpression.h"
#include "CharacterExpression.h"
#include "TimedExpressionMap.h"

#include "AudioTrack.h"

#include "FEMLParser.h"
#include "SAMLParser.h"
#include "BodyAnimationVector.h"

namespace Charanis {


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

		Ogre::SceneNode* facialNode;
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
		
		
		
	public:
		Character(Ogre::SceneManager* sceneManager, Ogre::SceneNode* parentNode, std::string meshName, DataManager* dm, std::string name, Ogre::Real scale=1);
		~Character();
		
		void importSAMLFile(std::string fileName);
		void importFEMLFile(std::string fileName);
		
		std::string getName();
		
		void setPosition(const Ogre::Vector3 pos);
		Ogre::Vector3 getPosition();
		
		void composeAnimations(std::string newAnimationName, Ogre::Animation* anim1, Ogre::Animation* anim2);
		void composeAnimations(std::string newAnimationName, std::vector<Ogre::Animation*> animVec);
		
		void addFKPerformance(FKPerformance* performance);
		void addFKPerformances(FKPerformanceVector* performanceVec);
		
		void addPerformance(CharacterPerformance* performance);
		void addPerformances(CharacterPerformanceVector* performanceVec);
		
		//void addSpeechExpression(Ogre::Real time, FacialExpression* exp);
		void addSpeechExpression(CharacterExpression* exp);
		void addSpeechExpressions(TimedExpressionMap* expressionMap);
		
		
		void addControlledExpression(CharacterExpression* exp);
		void addControlledExpressions(TimedExpressionMap* expressionMap);
		
		void playAudioTrack(Charanis::AudioTrack* track);
		void addAudioTrack(Charanis::AudioTrack* track);
		
		void playAnimations();
		
		void perform();
		

		
		void addWayPoint(const Ogre::Vector3 pos);
		Ogre::Vector3 getNextWayPoint();
		
		void setDirection(const Ogre::Vector3 direction);
		void rotate(const Ogre::Vector3 dir, const Ogre::Real timeSinceLastFrame);

		void walkPath(const Ogre::Real timeSinceLastFrame);
};

} // end of namespace

#endif