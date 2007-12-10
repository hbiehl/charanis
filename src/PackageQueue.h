/*
 *  PackageQueue.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 01.04.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef LAYER_CONNECTION_QUEUE
#define LAYER_CONNECTION_QUEUE


//#include "AnimationDataPackage.h"
#include "Package.h"

#include <time.h>

//#include "SDL/SDL_thread.h"
#include <boost/thread/thread.hpp>
#include <boost/thread/condition.hpp>
#include <boost/thread/xtime.hpp>
#include <boost/thread/mutex.hpp>

#include <deque>
#include <iostream>


namespace Charanis {

class PipelineLayer;

/**
 * \brief Warteschlange für die interne Kommunikation von %Charanis.
 *
 * Diese Warteschlange transportiert Objekte des Typs Package. Sie ist Threadsafe implementiert,
 * die Produzenten und Konsumenten von Paketen können also in verschiedenen Threads laufen.
 */

class PackageQueue {
	private:
		boost::mutex queue_mutex;
		boost::condition queueNotEmpty_condition;
		
		PipelineLayer* sourceLayer;
		PipelineLayer* destinationLayer;
		
		//SDL_sem *sem;
		typedef std::deque<Package*> PackageDeque;
		PackageDeque packageDeque;
	public:
		PackageQueue(PipelineLayer* sourceLayer, PipelineLayer* destinationLayer);
		~PackageQueue();
		
		PipelineLayer* getSourceLayer();
		PipelineLayer* getDestinationLayer();
		
		void setSourceLayer(PipelineLayer* sourceLayer);
		void setDestinationLayer(PipelineLayer* destinationLayer);
		
		/** Gibt die Anzahl der in der Queue enthaltenen Package-Objekte zurück **/
		int size();
		
		/** Fügt (vorne) ein neues Package-Objekt in die Queue ein **/
		void addPackage(Package* package);
		
		void addPriorityPackage(Package* package);
		
		/**
		 Entfernt das letzte (älteste) Package-Objekt aus der Queue und gibt einen Pointer darauf
		 zurück. Sollte die Queue leer sein, wird NULL zurückgegeben.
		 **/
		Package* getPackage();
};

} // end of namespace

#endif