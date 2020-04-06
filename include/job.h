#pragma once

#include <string>

struct Job {
    std::string jobname;
    std::string subject;
    time_t datetime;
    std::string selector;
    std::string tmplate;
};