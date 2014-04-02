/*
 * File:   Getter.cpp
 * Author: warren
 *
 * Created on October 31, 2012, 8:59 AM
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <random>
#include <QtCore>
#include <QString>
#include <QThread>
#include <QtGui>
#include <stdio.h>
#include "Custom.h"
#include "Getter.h"
#include "MainForm.h"
#include "ui_MainForm.h"

extern string pipeName;
extern string password;
extern qint64 startTime;
extern string beginBlockString;
extern string endBlockString;
extern string pipeName;
extern ofstream linssidLog;
extern bool closing;

using namespace std;

Getter::Getter() {
};

Getter::~Getter() {
};

void Getter::run() {
    // do stuff here
    exec();
}

MainForm* Getter::pMainForm;

const QEvent::Type Getter::DATA_WANTED_EVENT = static_cast<QEvent::Type> (DATAWANTED);
// Define the custom event subclass

class Getter::DataWantedEvent : public QEvent {
public:

    DataWantedEvent(const int customData1) :
    QEvent(Getter::DATA_WANTED_EVENT), wantedBlockNo(customData1) {
    }

    int getWantedBlockNo() const {
        return wantedBlockNo;
    }
private:
    int wantedBlockNo;
};

void Getter::postDataWantedEvent(const int customData1) {
    // This method (postDataWantedEvent) can be called from any thread
    QApplication::postEvent(this, new DataWantedEvent(customData1));
}

void Getter::customEvent(QEvent * event) {
    // When we get here, we've crossed the thread boundary and are now
    // executing in the Qt object's thread
    if (event->type() == Getter::DATA_WANTED_EVENT) {
        handleDataWantedEvent(static_cast<DataWantedEvent *> (event));
    }
    // use more else ifs to handle other custom events
}

void Getter::handleDataWantedEvent(const DataWantedEvent *event) {
    static fstream thePipe(pipeName);
    thePipe.flush();
    int blockNo = event->getWantedBlockNo();
    ostringstream cppIsStupid;
    cppIsStupid.str("");
    cppIsStupid << " " << blockNo;
    string lineCommand =
            "echo \"" + beginBlockString + cppIsStupid.str() + "\\n\" > " + pipeName;
    if (pwStatus == NOTNEEDED) {
        lineCommand += " && iwlist ";
    } else {
        lineCommand += " && echo \'" + password + "\' | sudo -kS -p \"\" iwlist ";
    }
    lineCommand += Getter::pMainForm->getCurrentInterface() + " scan > " + pipeName
            + " && echo \"" + endBlockString + cppIsStupid.str() + "\\n\" > " + pipeName;
    if (system(lineCommand.c_str()) != 0) {
        linssidLog << "Getter: command failed block " << blockNo << endl;
        thePipe << endBlockString << " -1" << endl; // signal error with -1 block number
    }
    Getter::pMainForm->postDataReadyEvent(blockNo);
    if (!closing)
        QThread::msleep(Getter::pMainForm->getNapTime() * 1000 + 500);
}