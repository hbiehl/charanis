/*
 *  FEMLParser.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 12.08.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef FEML_PARSER_H
#define FEML_PARSER_H

#include <string>
#include <iostream>
#include <vector>


#include "Parser.h"

#include "Ogre/OgreStringConverter.h"
#include "FacialExpression.h"

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/SAXException.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>


namespace Charanis {

typedef std::vector<FacialExpression*> FacialExpressionVector;

/**
 * \brief Parser zum Auswerten der FEML-Dateien.
 *
 * Dieser Parser wird verwendet, um Facial Expression Markup Language-Dateien auszuwerten.
 */
class FEMLParser : public Parser {
	private:
		std::string femlDir;
		
	public:
		FEMLParser(std::string femlDir);
		~FEMLParser();
		
		FacialExpressionVector* parseFile(std::string fileName);
};

} // end of namespace

#endif