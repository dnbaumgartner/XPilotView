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
