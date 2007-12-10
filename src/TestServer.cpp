/*
 *  TestClient.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 09.04.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "TestServer.h"




int main(int argc, char** argv) {
	QApplication app(argc, argv);
	
	TestServer::MainWindow* win = new TestServer::MainWindow();
	win->show();
	
	
	TestServer::NetworkThread* nt = new TestServer::NetworkThread(win, 9999);
	nt->run();
	win->setClientSocketList(nt->getClientSocketList());
	win->connect(nt->getClientSocketList(), SIGNAL(loggingSignal(QString)), win, SLOT(writeLog(QString)));
	
	return app.exec();
}