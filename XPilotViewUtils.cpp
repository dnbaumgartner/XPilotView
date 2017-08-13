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
 * File:   XPilotViewUtils.cpp
 * Author: dave
 * 
 * Created on August 12, 2017, 2:51 PM
 */

#include "XPilotViewUtils.hpp"

XPilotViewUtils::XPilotViewUtils()
{
}

XPilotViewUtils::~XPilotViewUtils()
{
}

void XPilotViewUtils::logMessage(std::string msg)
{
    XPLMDebugString(msg.c_str());
}

void XPilotViewUtils::logMessage(char* msg)
{
    XPLMDebugString(msg);
}
