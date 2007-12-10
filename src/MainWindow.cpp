/*
 *  MainWindow.cpp
 *  OgreTest
 *
 *  Created by Holger Biehl on 16.04.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "MainWindow.h"
#include <iostream>

namespace TestServer {
	
	MainWindow::MainWindow(QWidget* parent)
	: QWidget(parent) {
		messageLineEdit = new QLineEdit();
		sendButton = new QPushButton("Send");
		textBrowser = new QTextBrowser();
		logger = new QTextBrowser();
		
		layout = new QVBoxLayout();
		
		QHBoxLayout* hlayout = new QHBoxLayout();
		hlayout->addWidget(new QLabel("Message:"));
		hlayout->addWidget(messageLineEdit);
		
		
		
		
		layout->addLayout(hlayout);
		layout->addWidget(sendButton);
		
		
		QSplitter* splitter = new QSplitter(Qt::Vertical);
		layout->addWidget(splitter);
		
		QGroupBox* textBrowserGroup = new QGroupBox("Test");
		QVBoxLayout* textBrowserLayout = new QVBoxLayout();
		textBrowserLayout->addWidget(textBrowser);
		textBrowserGroup->setLayout(textBrowserLayout);
		splitter->addWidget(textBrowserGroup);
		
		QGroupBox* logGroup = new QGroupBox("Log");
		QVBoxLayout* logGroupLayout = new QVBoxLayout();
		logGroupLayout->addWidget(logger);
		logGroup->setLayout(logGroupLayout);
		
		splitter->addWidget(logGroup);
		

		
		setLayout(layout);

		
		connect(sendButton, SIGNAL(clicked()), this, SLOT(sendButtonClicked()));
	}

	
	
	
	MainWindow::~MainWindow() {}



	void MainWindow::setClientSocketList(ClientSocketList* clients) {
		clientSocketList = clients;
	}
	
	

	void MainWindow::sendButtonClicked() {
		writeLog("<b>[NET]</b> Sending message <i>\""+messageLineEdit->text()+"\"</i> to all clients<br>");
		clientSocketList->sendToAll(messageLineEdit->text().toStdString());
	}
	
	
	
	void MainWindow::writeLog(QString text) {
		if (logger != NULL) {
			QTextCursor cursor = logger->textCursor();
			cursor.movePosition(QTextCursor::End);
			logger->setTextCursor(cursor);
			QTime now = QTime::currentTime();
			logger->insertHtml(now.toString() +" "+ text);
		} else {
			std::cout << "Logger is NULL" << std::endl;
		}
	}
	
	
	
	void MainWindow::intSlot(int i) {
		std::ostringstream test;
		test << i << "Muh<br>" << std::endl;
		std::string str = test.str();
		logger->insertHtml(str.c_str());
	}
}