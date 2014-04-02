/* 
 * File:   passBox.h
 * Author: warren
 *
 * Created on December 2, 2012, 9:57 AM
 */

#ifndef _PASSBOX_H
#define	_PASSBOX_H

#include <iostream>
#include "ui_passBox.h"
#include "Custom.h"

extern std::string password;
extern passStatus pwStatus;

class passBox : public QDialog {
    Q_OBJECT
public:
    passBox();
    virtual ~passBox();
    void setPassPrompt(std::string);
public slots:    
    void passBtnAccept();
    void passBtnReject();    
private:
    Ui::passBox widget;
};

#endif	/* _PASSBOX_H */
