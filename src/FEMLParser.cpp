/*
 *  FEMLParser.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 12.08.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "FEMLParser.h"

// std includes
#include <iostream>

// dependency includes
//#include <Ogre/OgreStringConverter.h>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/SAXException.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>

// project includes
#include "FacialExpression.h"

namespace Charanis {

FEMLParser::FEMLParser(std::string femlDir) 
: Parser::Parser() {
	this->femlDir = femlDir;
}


FEMLParser::~FEMLParser() {
}


/*
 xercesc::DOMNodeList* FEMLParser::getNodeList(xercesc::DOMElement* parent, std::string nodeName) {
	XMLCh* xercesNodeName = XERCES_CPP_NAMESPACE::XMLString::transcode(nodeName.c_str());
	xercesc::DOMNodeList *nodeList = parent->getElementsByTagName(xercesNodeName);
	xercesc::XMLString::release(&xercesNodeName);
	return nodeList;
}

std::string FEMLParser::getStringContents(xercesc::DOMElement* element) {
	return xercesc::XMLString::transcode(element->getFirstChild()->getNodeValue());
}

Ogre::Real FEMLParser::getRealContents(xercesc::DOMElement* element) {
	return Ogre::StringConverter::parseReal(getStringContents(element));
}

std::string FEMLParser::getStringAttribute(xercesc::DOMElement* element, std::string attribute) {
	XMLCh* xercesAttribute = xercesc::XMLString::transcode(attribute.c_str());
	std::string value = XERCES_CPP_NAMESPACE::XMLString::transcode(element->getAttribute(xercesAttribute));
	xercesc::XMLString::release(&xercesAttribute);
	return value;
}

Ogre::Real FEMLParser::getRealAttribute(xercesc::DOMElement* element, std::string attribute) {
	return Ogre::StringConverter::parseReal(getStringAttribute(element, attribute));
}
*/

FacialExpressionVector* FEMLParser::parseFile(std::string fileName) {
	FacialExpressionVector* feVec = new FacialExpressionVector();
	
	std::string srcFile = femlDir + fileName;
	bool bFailed = false;

	parser->setCreateEntityReferenceNodes(false);
	try {
		
		//XercesString src(argv[1]);
		//const XMLCh* src = "Test";
		//XERCES_CPP_NAMESPACE::LocalFileInputSource source(src);
		parser->parse(srcFile.c_str());
		bFailed = parser->getErrorCount() != 0;
		if (bFailed) {
			std::cerr << "Parsing " << srcFile;
			std::cerr << " error count: " << parser->getErrorCount() << std::endl;
		}
	}
	catch (const XERCES_CPP_NAMESPACE::DOMException& e) {
		std::cerr << "DOM Exception parsing ";
		std::cerr << srcFile;
		std::cerr << " reports: ";
		// was message provided?
		if (e.msg) {
			// yes: display it as ascii.
			char *strMsg = XERCES_CPP_NAMESPACE::XMLString::transcode(e.msg);
			std::cerr << strMsg << std::endl;
			XERCES_CPP_NAMESPACE::XMLString::release(&strMsg);
		}
		else
		// no: just display the error code.
		std::cerr << e.code << std::endl;

		bFailed = true;
	}
	catch (const XERCES_CPP_NAMESPACE::XMLException& e) {
		std::cerr << "XML Exception parsing ";
		std::cerr << srcFile;
		std::cerr << " reports: ";
		std::cerr << e.getMessage() << std::endl;
		bFailed = true;
	}
	catch (const XERCES_CPP_NAMESPACE::SAXException& e) {
		std::cerr << "SAX Exception parsing ";
		std::cerr << srcFile;
		std::cerr << " reports: ";
		std::cerr << e.getMessage() << std::endl;
		bFailed = true;
	}
	catch (...) {
		std::cerr << "An exception parsing ";
		std::cerr << srcFile << std::endl;
		bFailed = true;
	}
	
	if (!bFailed) {
		XERCES_CPP_NAMESPACE::DOMDocument *pDoc = parser->getDocument();
		XERCES_CPP_NAMESPACE::DOMElement *docElement = pDoc->getDocumentElement();
		
		
		
		char *rootElement = xercesc::XMLString::transcode(docElement->getTagName());
		std::cout << "ROOT: " << XERCES_CPP_NAMESPACE::XMLString::transcode(docElement->getTagName()) << std::endl;
		xercesc::XMLString::release(&rootElement);

		
		
		XERCES_CPP_NAMESPACE::DOMNodeList* expressionList = getNodeList(docElement, "Expression");
		std::cout << "Number of Expressions: " << expressionList->getLength() << std::endl;
		for (int i=0; i<expressionList->getLength(); i++) {
			XERCES_CPP_NAMESPACE::DOMElement *expressionElement = (xercesc::DOMElement*) expressionList->item(i);
			
			XERCES_CPP_NAMESPACE::DOMNodeList* nameList = getNodeList(expressionElement, "Name");
			XERCES_CPP_NAMESPACE::DOMElement* nameElement = (xercesc::DOMElement*) nameList->item(0);
			
			FacialExpression* expression = new FacialExpression(getStringContents(nameElement));
			std::cout << "EXPRESSION_NAME=" << getStringContents(nameElement) << std::endl;
			
			xercesc::DOMNodeList* poseList = getNodeList(expressionElement, "Pose");
			for (int j=0; j<poseList->getLength(); j++) {
				xercesc::DOMElement* poseElement = (xercesc::DOMElement*) poseList->item(j);
				
				xercesc::DOMNodeList* morphTargetList = getNodeList(poseElement, "MorphTarget");
				for (int iMT=0; iMT<morphTargetList->getLength(); iMT++) {
					xercesc::DOMElement* morphTargetElement = (xercesc::DOMElement*) morphTargetList->item(iMT);
					std::cout << "\t\tAttribute id=" << getStringAttribute(morphTargetElement, "id") << std::endl;
					std::cout << "\t\tAttribute weight=" << getRealAttribute(morphTargetElement, "weight") << std::endl;
					
					expression->setPoseWeight(getStringAttribute(morphTargetElement, "id"), getRealAttribute(morphTargetElement, "weight"));
				}
			}
			feVec->push_back(expression);
		}
	}
	
	return feVec;
}

} // end of namespace