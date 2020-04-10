#pragma once

#include <string>
#include <map>

#include "property.h"

struct PropertyItem
{
    std::map<std::string, Property> properties;

    bool hasKey(std::string key)
    {
        std::map<std::string, Property>::iterator it = properties.find(key);
        return it != properties.end();
    }

    std::string get_value(std::string key) {
        return hasKey(key) ? properties[key].value : "";
    }
};