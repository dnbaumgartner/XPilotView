/*
 * This file is part of XPilotView.
 *
 * XPilotView is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * XPilotView is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with XPilotView.  If not, see <http://www.gnu.org/licenses/>
 */

/* 
 * File:   PreferencesPanel.hpp
 * Author: dave
 *
 * Created on August 7, 2017, 10:03 PM
 */

#ifndef _PREFERENCESPANEL_HPP
#define _PREFERENCESPANEL_HPP

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <memory>

#include <Qt>
#include "ui_PreferencesPanel.h"
#include "../XPilotView/KeyValueStore.hpp"

using namespace std;
using json = nlohmann::json;


class PreferencesPanel : public QMainWindow {
    Q_OBJECT
            
    KeyValueStore* preferences;
    
public:
    PreferencesPanel();
    virtual ~PreferencesPanel();


private slots:
    void on_ttyPathLineEdit_editingFinished();
    void on_rollScaleLineEdit_editingFinished();
    void on_pitchScaleLineEdit_editingFinished();
    void on_headingScaleLineEdit_editingFinished();
    void on_filterLagLineEdit_editingFinished();
    void on_savePushButton_clicked();

private:
    Ui::PreferencesPanel widget;
    void updateUI();
};

typedef std::shared_ptr<PreferencesPanel> PreferencesPanelPtr;

#endif /* _PREFERENCESPANEL_HPP */
