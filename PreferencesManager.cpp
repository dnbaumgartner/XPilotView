/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PreferencesManager.cpp
 * Author: dave
 * 
 * Created on August 8, 2017, 5:07 PM
 */

#include "PreferencesManager.hpp"

PreferencesPanelPtr PreferencesManager::prefPanel = NULL;
bool PreferencesManager::panelIsVisible = false;

PreferencesManager::PreferencesManager()
{
}

PreferencesManager::~PreferencesManager()
{
}

void PreferencesManager::togglePanel()
{
    if (panelIsVisible)
    {
        this->showPanel(false);
    } else
    {
        this->showPanel(true);
    }
}

PreferencesPanelPtr PreferencesManager::getPanel()
{
    if (prefPanel == NULL)
    {
        this->startGuiThread();
    }
    return prefPanel;
}

void PreferencesManager::showPanel(bool show)
{
    if (show)
    {
        if (prefPanel == NULL)
        {
            this->startGuiThread();
        }
        panelIsVisible = true;
        prefPanel->show();
    } else
    {
        if (prefPanel != NULL)
        {
            panelIsVisible = false;
            prefPanel->hide();
        }
    }
}

std::string PreferencesManager::getTTyPath()
{
    std::string result("");
    
    if (prefPanel == NULL)
    {
        this->startGuiThread();
    }
    result = prefPanel->getTTyPath();
    
    return result;
}

void *guiThread(void *arg)
{
    int argc = 1;
    char* argv[] = {"XPilotView"};

    try
    {
        QApplication app(argc, argv);

        // create and show your widgets here
        PreferencesManager::prefPanel = std::make_shared<PreferencesPanel>();

        app.exec();

    } catch (const std::exception& ex)
    {
        std::string msg(std::string("PreferencesManager::guiThread() : ") + ex.what());
        XPilotViewUtils::logMessage(msg);
    }

    pthread_exit(0);
}

void PreferencesManager::startGuiThread()
{
    pthread_t appThread;
    int ret;

    try
    {
        ret = pthread_create(&appThread, NULL, &guiThread, NULL);

        if (ret != 0)
        {
            exit(EXIT_FAILURE);
        }
        // wait for PreferencesPanel before proceeding
        while (PreferencesManager::prefPanel == NULL)
            std::this_thread::sleep_for(std::chrono::milliseconds(100));

    } catch (const std::exception& ex)
    {
        std::string msg(std::string("PreferencesManager::startGuiThread() : ") + ex.what());
        XPilotViewUtils::logMessage(msg);
    }
}