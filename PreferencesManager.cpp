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

PreferencesPanel* PreferencesManager::prefPanel = NULL;
bool PreferencesManager::panelIsVisible = false;

PreferencesManager::PreferencesManager()
{
}

PreferencesManager::~PreferencesManager()
{
    if(prefPanel != NULL)
    {
        prefPanel->setAttribute(Qt::WA_DeleteOnClose, true);
        prefPanel->close();
        //delete(prefPanel);
    }
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

PreferencesPanel* PreferencesManager::getPanel()
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
    if (prefPanel == NULL)
    {
        this->startGuiThread();
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
    PreferencesManager::prefPanel = new PreferencesPanel();

    app.exec();

    if (PreferencesManager::prefPanel != NULL)
    {
        delete(PreferencesManager::prefPanel);
        PreferencesManager::prefPanel = NULL;
    }
    PreferencesManager::panelIsVisible = false;

    pthread_exit(NULL);
}

void PreferencesManager::startGuiThread()
{
    pthread_t appThread;
    int ret;

    ret = pthread_create(&appThread, NULL, &guiThread, NULL);

    if (ret != 0)
    {
        exit(EXIT_FAILURE);
    }
    // wait for PreferencesPanel before proceeding
    while (PreferencesManager::prefPanel == NULL)
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
}