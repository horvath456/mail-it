#include "csv_utils.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreorder"
#pragma GCC diagnostic ignored "-Wdeprecated"
#pragma GCC diagnostic ignored "-Wunused-variable"
#include <csv/reader.hpp>
#pragma GCC diagnostic pop

#include <string>
#include <vector>

#include "receipent.h"

using namespace std;

vector<Receipent> CSV::read_recipient_list(string filename)
{
    csv::Reader reader;
    reader.read(filename);
    vector<Receipent> result{};
    return result;
}