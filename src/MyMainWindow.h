 /*************************************************************************
*   Copyright (C) 2009 by Christoph Eckert                                *
*   ce@christeck.de                                                       *
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
*   This program is distributed in the hope that it will be useful,       *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*   GNU General Public License for more details.                          *
*                                                                         *
*   You should have received a copy of the GNU General Public License     *
*   along with this program; if not, write to the                         *
*   Free Software Foundation, Inc.,                                       *
*   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
***************************************************************************/

#ifndef MYMAINWINDOW_h
#define MYMAINWINDOW_h

#include <iostream>

#include <alsa/asoundlib.h> 

#include <QSettings>
#include <QMessageBox>
#include <QFileDialog>
#include <QStatusBar>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMenuBar>
#include <QToolBar>
#include <QWhatsThis>

#include "ui_MainWindow.h"
#include "MidiIn.h"
#include "MidiOut.h"

#include "Versioning.h"

class MyMainWindow: public QMainWindow, private Ui::MainWindow
{
	Q_OBJECT

public:
	explicit MyMainWindow(QWidget* parent = nullptr);

protected:
	void dragEnterEvent(QDragEnterEvent*) override;
	void dropEvent(QDropEvent*) override;

	private:
	void setupMidi();
	void setupMenus();
	void setupConnections();
	void setupControls();
	void initGuiData();
	void prepareGuiData(std::vector<unsigned char>*);
	void displayGuiData();
	void createDatabase();

	bool confirmDataLoss();

	void trimMidiEvent(std::vector<unsigned char>*);
	void appendEvent(std::vector<unsigned char>*);

	QMessageBox* AboutBox;

	QString FilePath;
	QStringList deviceList;

	QString manufacturerName;
	QString modelName;
	QString modelImageFilename;
	QString deviceNumber;
	QString datatypeName;

	// I know string comparison sucks. But nevertheless...
	QString emptyImageString;
	QString unknownDataString;
	QString variousDataString;

	QAction* ActionHelpWhatsThis;

	MidiOut* midiOut;
	MidiIn* midiIn;

	// About vector usage see http://www.cppreference.com/cppvector/
	QList<std::vector<unsigned char>*> eventList;

	enum MidiStatus { idle, receiving, transmitting };
	MidiStatus midiStatus;

signals:
	void errorMessage(QString, QString);
	void statusMessage(QString, unsigned int);

public slots:
	void prepareOpenFile();
	void prepareReceiveFile();
	void prepareDiscardData();
	void prepareTransmitFile();
	bool prepareSaveFile();

	void loadFile(QString);
	void writeFile(QString);
	void transmitFile();

	void cancelTransmission();
	void discardData();
	void displayAboutBox();
	void displayErrorMessage(QString, QString);
	void setStatusbarText(QString, unsigned int);
	void chunkArrived();
	void eventArrived(QByteArray);
	void midiOutFinished();
	void eventSent(int, int);
};

#endif
