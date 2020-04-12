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

    std::map<std::string, std::string> get_other_properties()
    {
        std::map<std::string, std::string> result{};

        for (auto el : properties)
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

    std::string get_jobname()
    {
        return properties["jobname"].value;
    }

    void set_jobname(std::string v)
    {
        properties["jobname"] = Property{v};
    }

    std::string get_subject()
    {
        return properties["subject"].value;
    }

    void set_subject(std::string v)
    {
        properties["subject"] = Property{v};
    }

    std::string get_datetime()
    {
        return properties["datetime"].value;
    }

    void set_datetime(std::string v)
    {
        properties["datetime"] = Property{v};
    }

    std::string get_selector()
    {
        return properties["selector"].value;
    }

    void set_selector(std::string v)
    {
        properties["selector"] = Property{v};
    }

    std::string get_template()
    {
        return properties["template"].value;
    }

    void set_template(std::string v)
    {
        properties["template"] = Property{v};
    }
};