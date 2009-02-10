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

// std includes
#include <string>
#include <vector>

// project includes
#include "Parser.h"


namespace Charanis {

class FacialExpression;
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
