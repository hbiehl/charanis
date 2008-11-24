/*
 *  CharanisInfoPanel.cpp
 *  Charanis
 *
 *  Created by Holger Biehl on 01.01.08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
#include "CharanisInfoPanel.h"

// dependency includes
#include <Ogre/OgreOverlay.h>
#include <Ogre/OgreOverlayContainer.h>
#include <Ogre/OgreOverlayManager.h>
#include <Ogre/OgreStringConverter.h>
#include <Ogre/OgreTextAreaOverlayElement.h>


namespace Charanis {

CharanisInfoPanel::CharanisInfoPanel() {
	// Create a panel
	panel = static_cast<Ogre::OverlayContainer*>(
		Ogre::OverlayManager::getSingleton().createOverlayElement("Panel", "PanelName"));
	panel->setMetricsMode(Ogre::GMM_PIXELS);
	panel->setPosition(10, 10);
	panel->setDimensions(100, 100);


	// Create a text area
	timeTextArea = static_cast<Ogre::TextAreaOverlayElement*>(
		Ogre::OverlayManager::getSingleton().createOverlayElement("TextArea", "TimeTextArea"));
	timeTextArea->setMetricsMode(Ogre::GMM_PIXELS);
	timeTextArea->setPosition(10, 10);
	timeTextArea->setDimensions(80, 30);
	timeTextArea->setCaption("0");
	//timeTextArea->setHorizontalAlignment(Ogre::GHA_RIGHT);
	timeTextArea->setCharHeight(20);
	//timeTextArea->setFontName("StarWars");
	timeTextArea->setFontName("Charanis");
	timeTextArea->setColourBottom(Ogre::ColourValue(0.8, 0, 0));
	timeTextArea->setColourTop(Ogre::ColourValue(1, 0.7, 0));



	characterTextArea = static_cast<Ogre::TextAreaOverlayElement*>(
		Ogre::OverlayManager::getSingleton().createOverlayElement("TextArea", "CharacterTextArea"));
	characterTextArea->setMetricsMode(Ogre::GMM_PIXELS);
	characterTextArea->setPosition(10, 50);
	characterTextArea->setDimensions(80, 100);
	characterTextArea->setCaption("---");
	//timeTextArea->setHorizontalAlignment(Ogre::GHA_RIGHT);
	characterTextArea->setCharHeight(20);
	//characterTextArea->setFontName("StarWars");
	characterTextArea->setFontName("Charanis");
	characterTextArea->setColourBottom(Ogre::ColourValue(0.8, 0, 0));
	characterTextArea->setColourTop(Ogre::ColourValue(1, 0.7, 0));


	// Add the text area to the panel
	panel->addChild(timeTextArea);
	panel->addChild(characterTextArea);
	
	
	// Create an overlay, and add the panel
	Ogre::Overlay* overlay = Ogre::OverlayManager::getSingleton().create("OverlayName");
	overlay->add2D(panel);

	// Show the overlay
	overlay->show();
}


void CharanisInfoPanel::updateCharacterStats(const CharacterMap& characterMap) {
	std::string caption = "";
	for (CharacterMap::const_iterator it = characterMap.begin(); it != characterMap.end(); it++) {
		caption += it->first + "\n";
	}
	characterTextArea->setCaption(caption);
}


void CharanisInfoPanel::updateTimeStats(long time) {
	timeTextArea->setCaption(Ogre::StringConverter::toString(time));
}

} // end of namespace
