#pragma once

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreorder"
#pragma GCC diagnostic ignored "-Wdeprecated"
#pragma GCC diagnostic ignored "-Wunused-variable"
#include <csv/reader.hpp>
#pragma GCC diagnostic pop

#include <string>
#include <vector>

#include "receipent.h"

namespace CSV {
    std::vector<Receipent> read_recipient_list(std::string filename);
}