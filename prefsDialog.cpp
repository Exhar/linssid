/*
 * File:   Preferences.cpp
 * Author: warren
 *
 * Created on January 2, 2013, 2:40 PM
 */

#include <string>
#include <iostream>
#include "prefsDialog.h"
#include "MainForm.h"

struct sEntryValue {
    int plotMin;
    int plotMax;
    bool showGrid;
    bool logDataState;
} prefsDialog::entryValue;

prefsDialog::prefsDialog(int plotMin, int plotMax, bool showGrid, int logDataState, QObject* mommy) {
    widget.setupUi(this);
    prefsDialog::entryValue.plotMin = plotMin;
    prefsDialog::entryValue.plotMax = plotMax;
    prefsDialog::entryValue.showGrid = showGrid;
    prefsDialog::entryValue.logDataState = logDataState;
    // now set initial values of widgets in the prefs dialog
    widget.dbMinsb->setValue(plotMin);
    widget.dbMaxsb->setValue(plotMax);
    widget.plotGridcbx->setChecked(showGrid);
    widget.logDatacbx->setCheckState((Qt::CheckState) logDataState);
    // now finagle the upper and lower bounds of the spin boxes
    widget.dbMinsb->setMinimum(-100);
    widget.dbMaxsb->setMaximum(0);
    widget.dbMinsb->setMaximum(widget.dbMaxsb->value() - 10);
    widget.dbMaxsb->setMinimum(widget.dbMinsb->value() + 10);
    // disable user text editing the spin boxes. Yeah, this is the only way.
    widget.dbMinsb->findChild<QLineEdit*>()->setReadOnly(true);
    widget.dbMaxsb->findChild<QLineEdit*>()->setReadOnly(true);
    connect(prefsDialog::widget.dbMinsb, SIGNAL(valueChanged(int)), this, SLOT(minSbChanged(int)));
    connect(prefsDialog::widget.dbMaxsb, SIGNAL(valueChanged(int)), this, SLOT(maxSbChanged(int)));
    connect(prefsDialog::widget.plotGridcbx, SIGNAL(stateChanged(int)), this, SLOT(gridChanged(int)));
    connect(prefsDialog::widget.logDatacbx, SIGNAL(stateChanged(int)), mommy, SLOT(logPrefChanged(int)));
    connect(this, SIGNAL(plotPrefsChanged(int, int, bool)),
            mommy, SLOT(updatePlotPrefs(int, int, bool)));
    connect(this, SIGNAL(finished(int)), this, SLOT(bailOut(int)));
}

prefsDialog::~prefsDialog() {
}

void prefsDialog::minSbChanged(int newValue) {

    emit plotPrefsChanged(newValue, widget.dbMaxsb->value(), widget.plotGridcbx->isChecked());
    widget.dbMaxsb->setMinimum(newValue + 10);
}

void prefsDialog::maxSbChanged(int newValue) {

    emit plotPrefsChanged(widget.dbMinsb->value(), newValue, widget.plotGridcbx->isChecked());
    widget.dbMinsb->setMaximum(newValue - 10);
}

void prefsDialog::gridChanged(int newValue) {

    emit plotPrefsChanged(widget.dbMinsb->value(), widget.dbMaxsb->value(), newValue);
}

void prefsDialog::bailOut(int result) {
    if (result == 0)
        emit plotPrefsChanged(entryValue.plotMin, entryValue.plotMax, entryValue.showGrid);
}