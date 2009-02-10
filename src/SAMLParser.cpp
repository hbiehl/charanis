/*
 *  SAMLParser.cpp
 *  Charanis
 *
 *  Created by Holger Biehl on 06.12.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "SAMLParser.h"

// std includes
#include <iostream>
#include <vector>
// dependeny includes
#ifdef OSX
    #include <Ogre/Ogre.h>
#else
    #include <Ogre.h>
#endif
#include <xercesc/dom/DOM.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/sax/SAXException.hpp>
#include <xercesc/util/PlatformUtils.hpp>
// project includes
#include "BodyAnimation.h"

namespace Charanis {


SAMLParser::SAMLParser(std::string samlDir) 
: Parser::Parser() {
	this->samlDir = samlDir;
}


SAMLParser::~SAMLParser() {
}





BodyAnimationVector* SAMLParser::parseFile(Ogre::Entity* entity, std::string fileName) {
	BodyAnimationVector* baVector = new BodyAnimationVector();
	
	std::string srcFile = samlDir + fileName;
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

		
		
		XERCES_CPP_NAMESPACE::DOMNodeList* animationDefinitionList = getNodeList(docElement, "AnimationDefinition");
		std::cout << "Number of AnimationDefinitions: " << animationDefinitionList->getLength() << std::endl;
		for (int i=0; i<animationDefinitionList->getLength(); i++) {
			XERCES_CPP_NAMESPACE::DOMElement *animationDefinitionElement = (xercesc::DOMElement*) animationDefinitionList->item(i);
			
			XERCES_CPP_NAMESPACE::DOMNodeList* nameList = getNodeList(animationDefinitionElement, "Name");
			XERCES_CPP_NAMESPACE::DOMElement* nameElement = (xercesc::DOMElement*) nameList->item(0);
			std::string animationName = getStringContents(nameElement);
			
			BodyAnimation* anim = new BodyAnimation(animationName);
			std::cout << "ANIMATION_NAME=" << animationName << std::endl;
			
			Ogre::Real length = getRealContents((xercesc::DOMElement*) getNodeList(animationDefinitionElement, "Length")->item(0));
			Ogre::Real priority = getRealContents((xercesc::DOMElement*) getNodeList(animationDefinitionElement, "Priority")->item(0));
			// TODO: currently priority not used?!?
			
			
			Ogre::Skeleton* skeleton = entity->getSkeleton();
			if (skeleton->hasAnimation(animationName)) {
				std::cout << "======================  SAMLParser-Error ======================" << std::endl;
				std::cout << "Das Skelett vom Modell " << entity->getName() << " hat bereits eine Animation des Namens " << animationName << "." << std::endl;
				std::cout << "Die neue AnimationDefinition wird daher ignoriert." << std::endl;
				std::cout << "==================================================================" << std::endl;
				continue;
			}
			Ogre::Animation* ogreAnim = skeleton->createAnimation(animationName, length);
	
			
			// Auslesen der Gruppenzugehörigkeiten
			XERCES_CPP_NAMESPACE::DOMElement* groupsElement = (xercesc::DOMElement*) getNodeList(animationDefinitionElement, "Groups")->item(0);
			xercesc::DOMNodeList* groupList = getNodeList(groupsElement, "Group");
			for (int groupNo=0; groupNo<groupList->getLength(); groupNo++) {
				xercesc::DOMElement* groupElement = (xercesc::DOMElement*) groupList->item(groupNo);
				
				std::string groupName = getStringContents(groupElement);
				std::cout << "MEMBER OF GROUP "<< groupName << std::endl;
			}
			
			
			// Auslesen der AnimationTracks
			xercesc::DOMNodeList* animationTrackList = getNodeList(animationDefinitionElement, "AnimationTrack");
			for (int trackNo=0; trackNo<animationTrackList->getLength(); trackNo++) {
				xercesc::DOMElement* trackElement = (xercesc::DOMElement*) animationTrackList->item(trackNo);
				
				std::string boneName = getStringContents((xercesc::DOMElement*) getNodeList(trackElement, "BoneName")->item(0));
				std::cout << "BONE = "<< boneName << std::endl;
				
				
				
				
				Ogre::Bone* bone = NULL;
				try {
					bone = skeleton->getBone(boneName);
				} catch (...) {
					std::cout << "======================  SAMLParser-Error ======================" << std::endl;
					std::cout << "Das Modell vom  Modell " << entity->getName() << " hat keinen Knochen namens " << boneName << " in dem Skelett." << std::endl;
					std::cout << "Der entsprechende Track wird ignoriert." << std::endl;
					std::cout << "==================================================================" << std::endl;
					continue;
				}
				Ogre::NodeAnimationTrack* ogreTrack = ogreAnim->createNodeTrack(bone->getHandle(), bone);
			
				
				
				
				
				
				xercesc::DOMNodeList* keyFrameList = getNodeList(trackElement, "KeyFrame");
				for (int keyFrameNo=0; keyFrameNo<keyFrameList->getLength(); keyFrameNo++) {
					xercesc::DOMElement* keyFrameElement = (xercesc::DOMElement*) keyFrameList->item(keyFrameNo);
					
					Ogre::Real time = getRealContents((xercesc::DOMElement*) getNodeList(keyFrameElement, "Time")->item(0));
					std::cout << "\ttime = "<< time << std::endl;
					
					xercesc::DOMElement* rotationElement = (xercesc::DOMElement*) getNodeList(keyFrameElement, "Rotation")->item(0);
					Ogre::Real w = getRealContents((xercesc::DOMElement*) getNodeList(rotationElement, "W")->item(0));
					Ogre::Real x = getRealContents((xercesc::DOMElement*) getNodeList(rotationElement, "X")->item(0));
					Ogre::Real y = getRealContents((xercesc::DOMElement*) getNodeList(rotationElement, "Y")->item(0));
					Ogre::Real z = getRealContents((xercesc::DOMElement*) getNodeList(rotationElement, "Z")->item(0));
					std::cout << "\tRotation = "<< w << "," << x << "," << y << "," << z << std::endl;
					
					
				
					Ogre::TransformKeyFrame* ogreKf = ogreTrack->createNodeKeyFrame(time);
					ogreKf->setRotation(Ogre::Quaternion(w, x, y, z));
					
					std::cout << "\t------------------------" << std::endl;
				}
			}
			
			
			baVector->push_back(anim);
		}
	}
	
	return baVector;
}


} // end of namespace
