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
 * File:   PreferencesManager.hpp
 * Author: dave
 *
 * Created on August 8, 2017, 5:07 PM
 */

#ifndef PREFERENCESMANAGER_HPP
#define PREFERENCESMANAGER_HPP

#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <stdio.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

#include <QApplication>

#include "PreferencesPanel.hpp"

#include "XPilotViewUtils.hpp"
#include "KeyValueStore.hpp"

class PreferencesManager {
    KeyValueStore* preferences;
    
public:
    PreferencesManager();
    virtual ~PreferencesManager();

    void togglePanel();
    void showPanel(bool);
    PreferencesPanel* getPanel();

    static PreferencesPanel* prefPanel;
    static bool panelIsVisible;
    
private:
    void startGuiThread();
    void initPreferences();
    std::string getWorkingDirectory();

};

#endif /* PREFERENCESMANAGER_HPP */

