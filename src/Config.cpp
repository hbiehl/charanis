/*
 *  Config.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 24.08.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "Config.h"

namespace Charanis {

Config::Config(std::string configFilePath)
: Parser::Parser() {
	xercesc::DOMDocument* doc = Parser::parseFile(configFilePath);
	xercesc::DOMElement* rootElement = doc->getDocumentElement();
	
	hostName = getStringContents((xercesc::DOMElement*) getNodeList(rootElement, "Host")->item(0));
	port = getIntContents((xercesc::DOMElement*) getNodeList(rootElement, "Port")->item(0));
	femlDirectory = getStringContents((xercesc::DOMElement*) getNodeList(rootElement, "FEML-Dir")->item(0));
	samlDirectory = getStringContents((xercesc::DOMElement*) getNodeList(rootElement, "SAML-Dir")->item(0));
	soundDirectory = getStringContents((xercesc::DOMElement*) getNodeList(rootElement, "Sound-Dir")->item(0));
	
	std::cout << std::endl << std::endl << std::endl;
	std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$ CONFIGURATION FILE $$$$$$$$$$$$$$$$$$$$$$$" << std::endl;
	std::cout << "HostName=" << hostName << std::endl;
	std::cout << "Port=" << port << std::endl;
	std::cout << "FEML-Directory=" << femlDirectory << std::endl;
	std::cout << "SAML-Directory=" << samlDirectory << std::endl;
	std::cout << "FSound-Directory=" << soundDirectory << std::endl;
	std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << std::endl;
	std::cout << std::endl << std::endl << std::endl;
}

Config::~Config() {
}


std::string Config::getHostName() {
	return hostName;
}

int Config::getPort() {
	return port;
}


std::string Config::getFEMLDirectory() {
	return femlDirectory;
}


std::string Config::getSAMLDirectory() {
	return samlDirectory;
}

std::string Config::getSoundDirectory() {
	return soundDirectory;
}

} // end of namespace