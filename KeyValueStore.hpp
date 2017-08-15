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
 * File:   KeyValueStore.hpp
 * Author: dave
 *
 * Created on August 14, 2017, 11:45 AM
 */

#ifndef KEYVALUESTORE_HPP
#define KEYVALUESTORE_HPP

#include <iostream>
#include <fstream>
#include <exception>
#include <string>
#include <sys/stat.h>

#include "json.hpp"
#include "../XPilotView/XPilotViewUtils.hpp"

using json = nlohmann::json;

class KeyValueStore {
    std::string filePath;
    
public:
    KeyValueStore();
    virtual ~KeyValueStore();
    
    void setValue(std::string key, std::string value);
    std::string getValue(std::string key);
    int load(std::string filePath);
    int save();

    static KeyValueStore* Instance();
    
private:
    static KeyValueStore* instance;
    json jsonMap;
    
};

#endif /* KEYVALUESTORE_HPP */

