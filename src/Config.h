/*
 *  Config.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 24.08.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef CONFIG_H
#define CONFIG_H

// std includes
#include <string>
// project includes
#include "Parser.h"

namespace Charanis {


/**
 * \brief Verwaltung von Konfigurations-Parametern.
 * 
 * Diese Klasse verwaltet diverse Konfigurationsparameter von Charanis.
 * Bei Initialisierung des Objektes wird automatisch die angegebene Konfigurationsdatei
 * ausgewertet und der Inhalt in diesem Objekt zur späteren Abfrage gespeichert.
 * Andere Komponenten können über den DataManager Zugriff auf dieses Objekt erhalten.
 */

class Config : public Parser {
	private:
		std::string configFilePath;
		
		std::string hostName;
		int port;
		
		std::string femlDirectory;
		std::string samlDirectory;
		std::string soundDirectory;
	
	public:
		Config(std::string configFilePath);
		~Config();
		
		//void reload();
		//void save();
		
		std::string getHostName();
		int getPort();
		
		std::string getFEMLDirectory();
		std::string getSAMLDirectory();
		std::string getSoundDirectory();
};

} // end of namespace

#endif