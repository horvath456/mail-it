#pragma once

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreorder"
#pragma GCC diagnostic ignored "-Wdeprecated"
#pragma GCC diagnostic ignored "-Wunused-variable"
#include <csv/reader.hpp>
#pragma GCC diagnostic pop

#include <string>
#include <map>
#include <vector>

#include "receipent.h"

namespace CSV {
    std::vector<Receipent> read_receipent_list(std::string filename);
    std::vector<std::map<std::string, std::string>> read_jobfile(std::string filename);
}