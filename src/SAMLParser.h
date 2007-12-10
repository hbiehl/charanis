/*
 *  SAMLParser.h
 *  Charanis
 *
 *  Created by Holger Biehl on 06.12.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef SAML_PARSER_H
#define SAML_PARSER_H

#include <string>
#include <iostream>
#include <vector>

#include "SDL/SDL.h"
#include "Parser.h"


#include "Ogre/Ogre.h"
#include "Ogre/OgreStringConverter.h"
//#include "FacialExpression.h"
#include "BodyAnimationVector.h"

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/SAXException.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>


namespace Charanis {

//typedef std::vector<FacialExpression*> FacialExpressionVector;

/**
 * \brief Parser zum Auswerten der SAML-Dateien.
 *
 * Dieser Parser wird verwendet, um Skeleton Animation Markup Language-Dateien auszuwerten.
 */

class SAMLParser : public Parser {
	private:
		std::string samlDir;
		
	public:
		SAMLParser(std::string samlDir);
		~SAMLParser();
		
		BodyAnimationVector* parseFile(Ogre::Entity* entity, std::string fileName);
};


} // end of namespace

#endif