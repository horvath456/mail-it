#pragma once

#include <string>

struct Property
{
    Property(std::string v) : value{v} {}
    Property() : value{} {}
    std::string value;
};