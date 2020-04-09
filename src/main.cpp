#include <iostream>

#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>

#include <SQLiteCpp/SQLiteCpp.h>

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

    form fm;

    label lb{fm, rectangle{10, 10, 100, 100}};
    lb.caption("Hello, world!");

    fm.show();

    exec();
}
