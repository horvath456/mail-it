#pragma once

#include "property_item.h"

#include <string>
#include <map>

struct Receipent : public PropertyItem
{
    Receipent()
    {
        properties["vorname"] = Property{};
        properties["nachname"] = Property{};
        properties["email"] = Property{};
    }

    Receipent(std::string firstname, std::string lastname, std::string email)
    {
        properties["vorname"] = Property{firstname};
        properties["nachname"] = Property{lastname};
        properties["email"] = Property{email};
    }

    std::string get_first_name()
    {
        return properties["vorname"].value;
    }

    void set_first_name(std::string v)
    {
        properties["vorname"] = Property{v};
    }

    std::string get_last_name()
    {
        return properties["nachname"].value;
    }

    void set_last_name(std::string v)
    {
        properties["nachname"] = Property{v};
    }

    std::string get_email()
    {
        return properties["email"].value;
    }

    void set_email(std::string v)
    {
        properties["email"] = Property{v};
    }

    std::map<std::string, std::string> get_other_properties()
    {
        std::map<std::string, std::string> result{};

        for (auto el : properties)
        {
            if (el.first != "vorname" && el.first != "nachname" &&
                el.first != "email")
            {
                result[el.first] = el.second.value;
            }
        }

        return result;
    }
};