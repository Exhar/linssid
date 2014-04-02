/*
 * File:   passBox.cpp
 * Author: warren
 *
 * Created on December 2, 2012, 9:57 AM
 */

#include "passBox.h"
extern std::string password;
extern passStatus pwStatus;
using namespace std;

passBox::passBox() {
    widget.setupUi(this);
    connect( widget.passBtnBox, SIGNAL(accepted()), this, SLOT(passBtnAccept()));
    connect( widget.passBtnBox, SIGNAL(rejected()), this, SLOT(passBtnReject()));
    pwStatus = CANCELLED;
}

passBox::~passBox() {
}

void passBox::passBtnAccept() {
    password = passBox::widget.passEntry->text().toStdString();
    // test it with system call to sudo
    string cmdLine = "echo '" + password + "' | sudo -kSv -p \"\"";
    int rc = system(cmdLine.c_str());
    if (rc == 0) pwStatus = GOOD;
    else pwStatus = BAD;
}

void passBox::passBtnReject() {
    pwStatus = CANCELLED;
}

void passBox::setPassPrompt(string passPrompt) {
    passBox::widget.passLabel->setText(passPrompt.c_str());
}
