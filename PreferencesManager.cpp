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

        PreferencesManager::prefPanel = new PreferencesPanel();
        PreferencesManager::prefPanel->setAttribute(Qt::WA_DeleteOnClose);
        PreferencesManager::prefPanel->setAttribute(Qt::WA_QuitOnClose);

        app.exec();

    } catch (const std::exception& ex)
    {
        std::string msg(std::string("XPilotView: PreferencesManager::guiThread() : ") + ex.what());
        XPilotViewUtils::logMessage(msg);
    }
    
    PreferencesManager::prefPanel = NULL;
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
        std::string msg(std::string("XPilotView: PreferencesManager::startGuiThread() : ") + ex.what());
        XPilotViewUtils::logMessage(msg);
    }
}