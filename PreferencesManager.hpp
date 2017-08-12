/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
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

#include "../XPilotViewUI/PreferencesPanel.hpp"

#include "XPilotViewUtils.hpp"

class PreferencesManager {

public:
    PreferencesManager();
    virtual ~PreferencesManager();

    void togglePanel();
    void showPanel(bool);
    std::string getTTyPath();
    PreferencesPanelPtr getPanel();

    static PreferencesPanelPtr prefPanel;
    static bool panelIsVisible;
    
private:
    void startGuiThread();

};

#endif /* PREFERENCESMANAGER_HPP */

