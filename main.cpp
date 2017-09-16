/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.cpp
 * Author: dave
 *
 * Created on August 7, 2017, 10:01 PM
 */

#include <QApplication>
#include <qt5/QtWidgets/qwidget.h>
#include <pthread.h>

#include "PreferencesPanel.hpp"

void startAppThread();

int main(int argc, char *argv[])
{
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);
    startAppThread();
}

void *uiWorker(void *arg)
{
    int argc = 1;
    char* argv[] = {"XPilotView"};
    
    QApplication app(argc, argv);

    // create and show your widgets here
    PreferencesPanel panel;
    panel.show();

    app.exec();
    
    pthread_exit(NULL);
}

void startAppThread()
{
    pthread_t appThread;
    int ret;
    void *status;
    
    ret = pthread_create(&appThread, NULL, &uiWorker, NULL);
    if(ret != 0)
    {
        exit(EXIT_FAILURE);
    }
    pthread_join(appThread, &status);
}