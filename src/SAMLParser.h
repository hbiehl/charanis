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

// std includes
#include <string>

// dependency includes
#ifdef OSX
    #include <Ogre/OgreEntity.h>
#else
    #include <OgreEntity.h>
#endif

// project includes
#include "BodyAnimationVector.h"
#include "Parser.h"

namespace Charanis {

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
