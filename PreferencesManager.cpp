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

PreferencesPanel *prefPanel = NULL;

void startGuiThread();

PreferencesManager::PreferencesManager()
{
}

PreferencesManager::~PreferencesManager()
{
}

void PreferencesManager::showPreferences(bool show)
{
    if (show)
    {
        if (prefPanel == NULL)
        {
            startGuiThread();
        }
        prefPanel->show();
    }
    else
    {
        if (prefPanel != NULL)
        {
            prefPanel->hide();
        }
    }
}

std::string PreferencesManager::getTTyPath()
{
    if (prefPanel == NULL)
    {
        startGuiThread();
    }

    std::string result = prefPanel->getTTyPath();
    return result;
}

void *guiThread(void *arg)
{
    int argc = 1;
    char* argv[] = {"XPilotView"};

    QApplication app(argc, argv);

    // create and show your widgets here
    prefPanel = new PreferencesPanel();

    app.exec();

    if(prefPanel != NULL)
    {
        delete(prefPanel);
        prefPanel = NULL;
    }

    pthread_exit(NULL);
}

void startGuiThread()
{
    pthread_t appThread;
    int ret;
    
    ret = pthread_create(&appThread, NULL, &guiThread, NULL);

    if (ret != 0)
    {
        exit(EXIT_FAILURE);
    }
    while (prefPanel == NULL) // wait for PreferencesPanel before proceeding
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
}