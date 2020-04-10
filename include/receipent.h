#pragma once

#include "property_item.h"

#include <string>

struct Receipent : public PropertyItem
{
    Receipent()
    {
        properties["first_name"] = Property{};
        properties["last_name"] = Property{};
        properties["email"] = Property{};
    }

    Receipent(std::string firstname, std::string lastname, std::string email)
    {
        properties["first_name"] = Property{firstname};
        properties["last_name"] = Property{lastname};
        properties["email"] = Property{email};
    }

    Property get_first_name()
    {
        return properties["first_name"];
    }

    void set_first_name(Property p) {
        properties["first_name"] = p;
    }

    Property get_last_name()
    {
        return properties["last_name"];
    }

    void set_last_name(Property p) {
        properties["last_name"] = p;
    }

    Property get_email()
    {
        return properties["email"];
    }

    void set_email(Property p) {
        properties["email"] = p;
    }
};