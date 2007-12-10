/*
 *  MainWindow.h
 *  OgreTest
 *
 *  Created by Holger Biehl on 16.04.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QtGui/QApplication>
#include <QtGui/QWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QSplitter>
#include <QtGui/QPushButton>
#include <QtGui/QTextBrowser>
#include <QtGui/QLineEdit>
#include <QtGui/QLabel>
#include <QtGui/QGroupBox>
#include <QtGui/QTextCursor>
#include <QtCore/QTime>

#include <sstream>

#include "ClientSocketList.h"


namespace TestServer {



class MainWindow : public QWidget {
	Q_OBJECT
	
	private:
		ClientSocketList* clientSocketList;
		
		QLineEdit* messageLineEdit;
		QPushButton* sendButton;
		QTextBrowser* textBrowser;
		QTextBrowser* logger;
		QVBoxLayout* layout;
		
	public:
		MainWindow(QWidget* parent = 0);
		~MainWindow();
		
		void setClientSocketList(ClientSocketList* clients);
		
	public slots:
		void writeLog(QString text);
		void sendButtonClicked();
		void intSlot(int);
};

}

#endif