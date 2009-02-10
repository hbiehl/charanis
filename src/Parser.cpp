/*
 *  Parser.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 19.08.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "Parser.h"

// std includes
#include <iostream>
#include <vector>

// dependency includes
#ifdef OSX
    #include <Ogre/OgreStringConverter.h>
#else
    #include <OgreStringConverter.h>
#endif
#include <xercesc/sax/SAXException.hpp>
#include <xercesc/util/PlatformUtils.hpp>



namespace Charanis {

Parser::Parser() {
	std::cout << "Parser::Parser()" << std::endl;
	xercesc::XMLPlatformUtils::Initialize();
	parser = new xercesc::XercesDOMParser();
}


Parser::~Parser() {
	std::cout << "Parser::~Parser()" << std::endl;
	delete parser;
	xercesc::XMLPlatformUtils::Terminate();
}



 xercesc::DOMNodeList* Parser::getNodeList(xercesc::DOMElement* parent, std::string nodeName) {
	XMLCh* xercesNodeName = XERCES_CPP_NAMESPACE::XMLString::transcode(nodeName.c_str());
	xercesc::DOMNodeList *nodeList = parent->getElementsByTagName(xercesNodeName);
	xercesc::XMLString::release(&xercesNodeName);
	return nodeList;
}

std::string Parser::getStringContents(xercesc::DOMElement* element) {
	return xercesc::XMLString::transcode(element->getFirstChild()->getNodeValue());
}

Ogre::Real Parser::getRealContents(xercesc::DOMElement* element) {
	return Ogre::StringConverter::parseReal(getStringContents(element));
}


int Parser::getIntContents(xercesc::DOMElement* element) {
	return xercesc::XMLString::parseInt(element->getFirstChild()->getNodeValue());
}


std::string Parser::getStringAttribute(xercesc::DOMElement* element, std::string attribute) {
	XMLCh* xercesAttribute = xercesc::XMLString::transcode(attribute.c_str());
	std::string value = xercesc::XMLString::transcode(element->getAttribute(xercesAttribute));
	xercesc::XMLString::release(&xercesAttribute);
	return value;
}

Ogre::Real Parser::getRealAttribute(xercesc::DOMElement* element, std::string attribute) {
	return Ogre::StringConverter::parseReal(getStringAttribute(element, attribute));
}

int Parser::getIntAttribute(xercesc::DOMElement* element, std::string attribute) {
	XMLCh* xercesAttribute = xercesc::XMLString::transcode(attribute.c_str());
	int value = xercesc::XMLString::parseInt(element->getAttribute(xercesAttribute));
	xercesc::XMLString::release(&xercesAttribute);
	return value;
}


xercesc::DOMDocument* Parser::parseFile(std::string path) {
	bool bFailed = false;

	parser->setCreateEntityReferenceNodes(false);
	try {
		
		//XercesString src(argv[1]);
		//const XMLCh* src = "Test";
		//XERCES_CPP_NAMESPACE::LocalFileInputSource source(src);
		parser->parse(path.c_str());
		bFailed = parser->getErrorCount() != 0;
		if (bFailed) {
			std::cerr << "Parsing " << path;
			std::cerr << " error count: " << parser->getErrorCount() << std::endl;
		}
	}
	catch (const XERCES_CPP_NAMESPACE::DOMException& e) {
		std::cerr << "DOM Exception parsing ";
		std::cerr << path;
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
		std::cerr << path;
		std::cerr << " reports: ";
		std::cerr << e.getMessage() << std::endl;
		bFailed = true;
	}
	catch (const XERCES_CPP_NAMESPACE::SAXException& e) {
		std::cerr << "SAX Exception parsing ";
		std::cerr << path;
		std::cerr << " reports: ";
		std::cerr << e.getMessage() << std::endl;
		bFailed = true;
	}
	catch (...) {
		std::cerr << "An exception parsing ";
		std::cerr << path << std::endl;
		bFailed = true;
	}
	
	if (!bFailed) {
		return parser->getDocument();
	} else {
		return NULL;
	}
}

} // end of namespace
