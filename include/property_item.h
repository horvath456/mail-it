#pragma once

#include <string>
#include <map>

#include "property.h"

struct PropertyItem
{
    std::map<std::string, Property> properties;

    bool has_key(std::string key)
    {
        std::map<std::string, Property>::iterator it = properties.find(key);
        return it != properties.end();
    }

    std::string get_value(std::string key) {
        return has_key(key) ? properties[key].value : "";
    }

    void set_property(std::string name, std::string value) {
        properties[name] = Property{value};
    }

    std::string get_property(std::string name) {
        return properties[name].value;
    }
};