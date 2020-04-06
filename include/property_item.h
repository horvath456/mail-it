#pragma once

#include <string>
#include <map>

#include "property.h"

struct PropertyItem {
    std::map<std::string, Property> properties;
};