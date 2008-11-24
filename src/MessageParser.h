/*
 *  MessageParser.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 19.08.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef MESSAGE_PARSER_H
#define MESSAGE_PARSER_H

// std includes
#include <string>
#include <vector>
// dependency includes
#include <Ogre/Ogre.h>
// project includes
#include "Parser.h"
#include "Package.h"

namespace Charanis {

class EngineManager;


/**
 * \brief Parser zum Auswerten der CharanisML-Nachrichten.
 *
 * Dieser Parser wird von NetworkLayer verwendet, um die eingehenden CharanisML-Nachrichten
 * auszuwerten.
 */
class MessageParser : public Parser {
	private:
		//DataManager* dataManager;
		EngineManager* engineManager;

		Ogre::ColourValue* getColour(xercesc::DOMElement* parentElement);
		Ogre::Vector3* getVector(xercesc::DOMElement* parentElement);
		Ogre::Quaternion* getQuaternion(xercesc::DOMElement* parentElement);
	
		void parseSceneControl(xercesc::DOMElement* sceneControlElement, std::vector<Package*>* packageVector);
		void parseCharacterControl(xercesc::DOMElement* characterControlElement, std::vector<Package*>* packageVector, Ogre::Real packageLength);
		
	public:
		//NewMessageParser(DataManager* dataManager);
		MessageParser(EngineManager* engineManager);
		~MessageParser();
		

		std::vector<Package*>* parseXmlMessage(std::string message);//, Ogre::Real time);
};

} // end of namespace

#endif