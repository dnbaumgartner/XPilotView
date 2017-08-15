/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   KeyValueStore.cpp
 * Author: dave
 * 
 * Created on August 14, 2017, 11:45 AM
 */

#include "KeyValueStore.hpp"

KeyValueStore* KeyValueStore::instance = NULL;
json jsonMap;

KeyValueStore::KeyValueStore()
{
}

KeyValueStore::~KeyValueStore()
{
}

KeyValueStore* KeyValueStore::Instance()
{
    if(instance == NULL) {
        instance = new KeyValueStore();
    }
    return instance;
}

void KeyValueStore::setValue(std::string key, std::string value)
{
    jsonMap[key] = value;
}

std::string KeyValueStore::getValue(std::string key)
{
    return jsonMap[key];
}

int KeyValueStore::load(std::string filePath)
{
    int result = -1;
    struct stat st;

    this->filePath = filePath;
    
    if (this->filePath.length() > 0)
    {
        if (stat(this->filePath.c_str(), &st) == 0) // file exist?
        {
            try
            {
                std::ifstream ifs(this->filePath, std::ofstream::in);
                if (ifs.good())
                {
                    ifs >> jsonMap;
                }
                ifs.close();
                result = 0;

            } catch (const std::exception& ex)
            {
                XPilotViewUtils::logMessage(std::string("XPilotView:KeyValueStore:load failed: ") + ex.what());
            }
        }
    }
    return result;
}

int KeyValueStore::save()
{
    int result = -1;

    if (this->filePath.length() > 0)
    {
        try
        {
            std::ofstream ofs(this->filePath, std::ofstream::out);
            ofs << std::setw(4) << jsonMap << std::endl;
            ofs.close();
            result = 0;

        } catch (const std::exception& ex)
        {
            XPilotViewUtils::logMessage(std::string("XPilotView:KeyValueStore:save failed: ") + ex.what());
        }
    }

    return result;
}
