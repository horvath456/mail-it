#pragma once

#include "property_item.h"

struct Job : private PropertyItem {
    Job() {
        properties["jobname"] = Property{};
        properties["subject"] = Property{};
        properties["datetime"] = Property{};
        properties["selector"] = Property{};
        properties["template"] = Property{};
    }

    Property get_jobname()
    {
        return properties["jobname"];
    }

    void set_jobname(Property p) {
        properties["jobname"] = p;
    }

    Property get_subject()
    {
        return properties["subject"];
    }

    void set_subject(Property p) {
        properties["subject"] = p;
    }

    Property get_datetime()
    {
        return properties["datetime"];
    }

    void set_datetime(Property p) {
        properties["datetime"] = p;
    }

    Property get_selector()
    {
        return properties["selector"];
    }

    void set_selector(Property p) {
        properties["selector"] = p;
    }

    Property get_template()
    {
        return properties["template"];
    }

    void set_template(Property p) {
        properties["template"] = p;
    }
};