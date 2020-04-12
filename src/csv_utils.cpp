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
    vector<Receipent> result{};

    csv::Reader reader;
    reader.read(filename);

    auto rows = reader.rows();
    for (auto &row : rows)
    {
        Receipent r{row["Vorname"], row["Nachname"], row["Email"]};
        r.properties["Klasse"] = row["Klasse"];
        r.properties["Benutzername"] = row["Benutzername"];
        r.properties["Kennwort"] = row["Kennwort"];
        r.properties["ID"] = row["ID"];

        result.push_back(r);
    }

    return result;
}