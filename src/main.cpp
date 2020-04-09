#include <iostream>

#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>

#include <SQLiteCpp/SQLiteCpp.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreorder"
#pragma GCC diagnostic ignored "-Wdeprecated"
#pragma GCC diagnostic ignored "-Wunused-variable"
#include <csv/reader.hpp>
#pragma GCC diagnostic pop

#include "config.h"
#include "job.h"
#include "receipent.h"

using namespace std;
using namespace nana;

int main()
{
    Config cfg{};
    Job job{};
    Receipent r{};

    SQLite::Database db("test.db3", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

    csv::Reader foo;
    foo.read("test.csv");

    form fm;

    label lb{fm, rectangle{10, 10, 100, 100}};
    lb.caption("Hello, world!");

    fm.show();

    exec();
}
