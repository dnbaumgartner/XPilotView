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

void *GyroManagerThread(void *arg);

std::string GyroManager::ttyPath = "/dev/ttyUSB0";
bool GyroManager::isRunnable = false;

unsigned int sfd;
struct termios savetty;

GyroAnglesPtr angles = std::make_shared<GyroAngles>();

GyroManager::GyroManager()
{
}

GyroManager::GyroManager(std::string ttyPath)
{
    this->setTTyPath(ttyPath);
}

GyroManager::~GyroManager()
{
    this->stop();
}

void GyroManager::setTTyPath(std::string ttyPath)
{
    this->ttyPath = ttyPath;
}

std::string GyroManager::getTTyPath()
{
    return this->ttyPath;
}

void GyroManager::start()
{
    this->isRunnable = true;
    this->startManagerThread(this->ttyPath);
}

void GyroManager::stop()
{
    this->isRunnable = false;
    tcsetattr(sfd, TCSANOW, &savetty);
    close(sfd);
}

GyroAnglesPtr GyroManager::getAngles()
{
    return angles;
}

void GyroManager::startManagerThread(std::string ttypath)
{
    sfd = this->opentty(ttypath);
    this->initGyro();
    
    pthread_t gmthread;
    int ret = 0;
    
    ret = pthread_create(&gmthread, NULL, &GyroManagerThread, NULL);
}

void *GyroManagerThread(void *arg)
{
    unsigned char buf[80];

    while (true)
    {
        int rdlen = read(sfd, buf, 1);

        if (rdlen > 0)
        {
            if (buf[0] == 0x55)
            {
                rdlen = read(sfd, &buf[1], 10);
                if (buf[1] == 0x53)
                {
                    float a[3];
                    GyroManager::decode(buf, a);
                    angles = std::make_shared<GyroAngles>(a[0], a[1], a[2]);
                }
            }
        }
    }
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

