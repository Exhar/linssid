/* 
 * File:   Preferences.h
 * Author: warren
 *
 * Created on January 2, 2013, 2:40 PM
 */

#ifndef _PREFERENCES_H
#define	_PREFERENCES_H

#include "ui_prefsDialog.h"

struct sEntryValue;

class prefsDialog : public QDialog {
    Q_OBJECT
public:
    prefsDialog(int, int, bool, int, QObject*);
    virtual ~prefsDialog();
    static sEntryValue entryValue;
public slots:
    //    void returnPrefsOK();
    void bailOut(int);
    void minSbChanged(int);
    void maxSbChanged(int);
    void gridChanged(int);
    //    void interceptClose(int);
signals:
    void plotPrefsChanged(int, int, bool);
private:
    Ui::prefsDialog widget;
};

#endif	/* _PREFERENCES_H */
