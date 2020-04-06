#pragma once

#include <string>

class Job {
    std::string jobname;
    std::string subject;
    time_t datetime;
    std::string selector;
    std::string tmplate;
};