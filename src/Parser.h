/*
 *  Parser.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 19.08.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef PARSER_H
#define PARSER_H


#include <string>
#include <iostream>
#include <vector>

#include "Ogre/OgreStringConverter.h"

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/SAXException.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>

namespace Charanis {

class Parser {
	protected:
		xercesc::XercesDOMParser* parser;
		
		xercesc::DOMNodeList* getNodeList(xercesc::DOMElement* parent, std::string nodeName);
		
		std::string getStringContents(xercesc::DOMElement* element);
		Ogre::Real getRealContents(xercesc::DOMElement* element);
		int getIntContents(xercesc::DOMElement* element);
		
		std::string getStringAttribute(xercesc::DOMElement* element, std::string attribute);
		Ogre::Real getRealAttribute(xercesc::DOMElement* element, std::string attribute);
		int getIntAttribute(xercesc::DOMElement* element, std::string attribute);
	
		xercesc::DOMDocument* Parser::parseFile(std::string pathToFile);
		
	public:
		Parser();
		~Parser();
};

} // end of namespace

#endif