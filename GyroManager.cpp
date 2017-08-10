/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GyroManager.cpp
 * Author: dave
 * 
 * Created on August 4, 2017, 8:58 PM
 */

#include "GyroManager.hpp"


bool GyroManager::isRunning = false;
bool GyroManager::setCenterView = false;
unsigned int GyroManager::sfd;
json* GyroManager::gyroPrefs = NULL;
GyroAngles GyroManager::viewCenter(0.0, 0.0, 0.0);
GyroAnglesPtr GyroManager::angles = std::make_shared<GyroAngles>(0.0, 0.0, 0.0);

GyroManager::GyroManager()
{
    //viewCenter.setAngles(0.0, 0.0, 0.0);
}

GyroManager::~GyroManager()
{
    this->stop();
}

void GyroManager::start()
{
    this->isRunning = true;
    if (gyroPrefs == NULL) gyroPrefs = prefMgr.getPanel()->getPreferences();
    this->startManagerThread();
}

void GyroManager::stop()
{
    this->isRunning = false;
    sleep(1); // wait for thread loop to exit
    tcsetattr(sfd, TCSANOW, &savetty);
    close(sfd);
}

GyroAnglesPtr GyroManager::getAngles()
{
    return GyroManager::angles;
}

void GyroManager::showPreferences(bool show)
{
    prefMgr.showPanel(show);
}

void GyroManager::togglePreferencesPanel()
{
    prefMgr.togglePanel();
}

std::string GyroManager::getTTyPath()
{
    return prefMgr.getTTyPath();
}

void GyroManager::setViewCenter()
{
    setCenterView = true;
}

void *GyroManagerThread(void *arg)
{
    unsigned char buf[80];
    float a[3];

    while (GyroManager::isRunning)
    {
        int rdlen = read(GyroManager::sfd, buf, 1);

        if (rdlen > 0)
        {
            if (buf[0] == 0x55)
            {
                rdlen = read(GyroManager::sfd, &buf[1], 10);
                if (buf[1] == 0x53)
                {
                    string hscale = (*GyroManager::gyroPrefs)["horizScale"];
                    float hscalef = std::stof(hscale);
                    string vscale = (*GyroManager::gyroPrefs)["vertScale"];
                    float vscalef = std::stof(vscale);
                    std::cout << "hscale= " << hscalef << " vscale= " << vscalef << std::endl;

                    GyroManager::decode(buf, a);
                    std::cout << "x= " << a[0] << "y= " << a[1] << "z= " << a[2] << std::endl;

                    AngleSet center = GyroManager::viewCenter.getAngleSet();
                    float x = (a[0] - center.x) * hscalef;
                    float y = (a[1] - center.y) * vscalef;
                    float z = (a[2] - center.z);
                    std::cout << "GyroMgr: x= " << x << " y= " << y << std::endl;

                    GyroManager::angles->setAngles(x, y, z);
                    //std::cout << "GyroMgr: angles.x= "  << angles->x << " angles.y= " << angles->y << std::endl;

                    if (GyroManager::setCenterView)
                    {
                        GyroManager::viewCenter.setAngles(a[0], a[1], a[2]);
                        GyroManager::setCenterView = false;
                    }
                }
            }
        }
    }
}

void GyroManager::startManagerThread()
{
    std::string ttypath = prefMgr.getTTyPath();
    sfd = this->opentty(ttypath);
    this->initGyro();

    pthread_t gmthread;
    int ret = 0;

    ret = pthread_create(&gmthread, NULL, &GyroManagerThread, NULL);
}

unsigned int GyroManager::opentty(std::string ttypath)
{
    unsigned int sfd;
    speed_t spd = B115200;
    struct termios tty;
    int rc;

    sfd = open(ttypath.c_str(), O_RDWR | O_NOCTTY);
    if (sfd < 0) return -1;

    rc = tcgetattr(sfd, &tty);
    if (rc < 0) return -2;
    savetty = tty; /* preserve original settings for restoration */

    cfsetospeed(&tty, spd);
    cfsetispeed(&tty, spd);

    cfmakeraw(&tty);

    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 10;

    tty.c_cflag &= ~PARENB; // no parity bit
    tty.c_cflag &= ~CSTOPB; // one stop bit
    tty.c_cflag &= ~CRTSCTS; // no HW flow control
    tty.c_cflag |= CLOCAL | CREAD;
    rc = tcsetattr(sfd, TCSANOW, &tty);
    if (rc < 0) return -3;

    return sfd;
}

void GyroManager::initGyro()
{
    unsigned char cmdZeroz[] = {0xff, 0xaa, 0x52};
    unsigned char cmdUseSerial[] = {0xff, 0xaa, 0x61};
    unsigned char cmdUseI2C[] = {0xff, 0xaa, 0x62};
    unsigned char cmdBaud115200[] = {0xff, 0xaa, 0x63};
    unsigned char cmdBaude9600[] = {0xff, 0xaa, 0x64};

    int wrlen = write(sfd, cmdZeroz, sizeof (cmdZeroz));
    if (wrlen != sizeof (cmdZeroz)) printf("write cmdZeros failed: %d\n", errno);
    wrlen = write(sfd, cmdUseSerial, sizeof (cmdZeroz));
    if (wrlen != sizeof (cmdUseSerial)) printf("write cmdUseSerial failed: %d\n", errno);
    wrlen = write(sfd, cmdBaude9600, sizeof (cmdZeroz));
    if (wrlen != sizeof (cmdBaude9600)) printf("write cmdBaude9600 failed: %d\n", errno);
}

void GyroManager::decode(unsigned char buf[], float result[])
{
    if (buf[0] == 0x55)
    {
        switch (buf [1]) {
            case 0x51:
                result[0] = (short(buf [3] << 8 | buf [2])) / 32768.0 * 16;
                result[1] = (short(buf [5] << 8 | buf [4])) / 32768.0 * 16;
                result[2] = (short(buf [7] << 8 | buf [6])) / 32768.0 * 16;
                break;
            case 0x52:
                result[0] = (short(buf [3] << 8 | buf [2])) / 32768.0 * 2000;
                result[1] = (short(buf [5] << 8 | buf [4])) / 32768.0 * 2000;
                result[2] = (short(buf [7] << 8 | buf [6])) / 32768.0 * 2000;
                break;
            case 0x53:
                result[0] = (short(buf [3] << 8 | buf [2])) / 32768.0 * 180;
                result[1] = (short(buf [5] << 8 | buf [4])) / 32768.0 * 180;
                result[2] = (short(buf [7] << 8 | buf [6])) / 32768.0 * 180;
                break;
        }
    }
}

