#pragma once

#include "property_item.h"

struct Receipent : public PropertyItem
{
    Receipent()
    {
        properties["first_name"] = Property{};
        properties["last_name"] = Property{};
        properties["email"] = Property{};
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