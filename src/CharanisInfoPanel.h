/*
 *  CharanisInfoPanel.h
 *  Charanis
 *
 *  Created by Holger Biehl on 01.01.08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef CHARANIS_INFO_PANEL_H
#define CHARANIS_INFO_PANEL_H

#include "Ogre/Ogre.h"
#include "Ogre/OgreTextAreaOverlayElement.h"


#include "CharacterMap.h"

namespace Charanis {


	class CharanisInfoPanel {
		private:
			Ogre::OverlayContainer* panel;
			
			Ogre::TextAreaOverlayElement* timeTextArea;
			Ogre::TextAreaOverlayElement* characterTextArea;
		
		public:
			CharanisInfoPanel();
			void updateCharacterStats(const CharacterMap&);
			void updateTimeStats(long time);
	};

} // end of namespace


#endif