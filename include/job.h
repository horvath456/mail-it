#pragma once

#include "property_item.h"

struct Job : public PropertyItem
{
    Job()
    {
        properties["jobname"] = Property{};
        properties["subject"] = Property{};
        properties["datetime"] = Property{};
        properties["selector"] = Property{};
        properties["template"] = Property{};
    }

    std::map<std::string, std::string> get_other_properties() const
    {
        std::map<std::string, std::string> result{};

        for (const auto &el : properties)
        {
            if (el.first != "jobname" && el.first != "subject" &&
                el.first != "datetime" && el.first != "selector" &&
                el.first != "template")
            {
                result[el.first] = el.second.value;
            }
        }

        return result;
    }

    std::string get_jobname() const
    {
        return properties.at("jobname").value;
    }

    void set_jobname(std::string v)
    {
        properties["jobname"] = Property{v};
    }

    std::string get_subject() const
    {
        return properties.at("subject").value;
    }

    void set_subject(std::string v)
    {
        properties["subject"] = Property{v};
    }

    std::string get_datetime() const
    {
        return properties.at("datetime").value;
    }

    void set_datetime(std::string v)
    {
        properties["datetime"] = Property{v};
    }

    std::string get_selector() const
    {
        return properties.at("selector").value;
    }

    void set_selector(std::string v)
    {
        properties["selector"] = Property{v};
    }

    std::string get_template() const
    {
        return properties.at("template").value;
    }

    void set_template(std::string v)
    {
        properties["template"] = Property{v};
    }
};