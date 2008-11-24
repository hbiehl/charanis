/*
 *  PackageQueue.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 01.04.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#include "PackageQueue.h"

// std includes
#include <iostream>
// dependeny includes
#include <boost/thread/xtime.hpp>
// project includes
#include "Package.h"
#include "PipelineLayer.h"


namespace Charanis {

PackageQueue::PackageQueue(PipelineLayer* sourceLayer, PipelineLayer* destinationLayer) {
	this->sourceLayer = sourceLayer;
	this->destinationLayer = destinationLayer;
}


PackageQueue::~PackageQueue() {
	std::cout << "%%% Desctructor PackageQueue - BEGIN %%%" << std::endl;
	// Delete All Packages in the Queue
	PackageDeque::iterator it;
	for (it = packageDeque.begin(); it!=packageDeque.end(); it++) {
		delete (*it);
	}
	packageDeque.clear();
	
	// Remove References to this queue within the source and destination layer
	if (sourceLayer != NULL) {
		sourceLayer->setOutputQueue(NULL);
	}
	if (destinationLayer != NULL) {
		destinationLayer->setInputQueue(NULL);
	}
	std::cout << "%%% Desctructor PackageQueue - END %%%" << std::endl;
}

		
PipelineLayer* PackageQueue::getSourceLayer() {
	return sourceLayer;
}


PipelineLayer* PackageQueue::getDestinationLayer() {
	return destinationLayer;
}

		
void PackageQueue::setSourceLayer(PipelineLayer* sourceLayer) {
	this->sourceLayer = sourceLayer;
}


void PackageQueue::setDestinationLayer(PipelineLayer* destinationLayer) {
	this->destinationLayer = destinationLayer;
}
		
		
		
int PackageQueue::size() {
	boost::mutex::scoped_lock lock(queue_mutex);
	int size = packageDeque.size();
	return size;
}


void PackageQueue::addPackage(Package* package) {
	//std::cout << "ADDING PACKAGE IN QUEUE "<< destinationLayer->getName() <<" [BEGIN]" << std::endl;
	//std::cout << "AAAAAAAAAAAAA" << std::endl;
	boost::mutex::scoped_lock lock(queue_mutex);
	//std::cout << "BBBBBBBBBBBBB" << std::endl;
	packageDeque.push_front(package);
	//std::cout << "CCCCCCCCCCCCC" << std::endl;
	queueNotEmpty_condition.notify_one();
	//std::cout << "DDDDDDDDDDDDD" << std::endl;
	//std::cout << "ADDING PACKAGE IN QUEUE "<< destinationLayer->getName() <<" [END]" << std::endl;
}


void PackageQueue::addPriorityPackage(Package* package) {
	boost::mutex::scoped_lock lock(queue_mutex);
	packageDeque.push_back(package);
	queueNotEmpty_condition.notify_one();
}

Package* PackageQueue::getPackage() {
	//std::cout << "GET_PACKAGE " << destinationLayer->getName() <<" [BEGIN]" << std::endl;
	boost::mutex::scoped_lock lock(queue_mutex);
	
	if (packageDeque.size()<=0) { // no package in queue
		//std::cout << destinationLayer->getName() << ": Waiting for a package in the Queue..." << std::endl; 
		//time_t curTime = time (NULL);

		
		boost::xtime xt;
		boost::xtime_get(&xt, boost::TIME_UTC);
		xt.sec += 1;
		
		//std::cout << "BEFORE TIMED_WAIT" << std::endl;
		queueNotEmpty_condition.timed_wait(lock, xt);
		//std::cout << "AFTER TIMED_WAIT" << std::endl;
	}
	
	Package* package = NULL;
	if (packageDeque.size()>0) {
		package = packageDeque.back();
		packageDeque.pop_back();
	}
	//std::cout << "GET_PACKAGE " << destinationLayer->getName() <<" [END]" << std::endl;
	return package;
}

} // end of namespace