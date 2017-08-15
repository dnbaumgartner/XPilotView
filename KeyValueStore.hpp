/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
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

