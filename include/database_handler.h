#pragma once

#include <SQLiteCpp/SQLiteCpp.h>
#include "receipent.h"

class DatabaseHandler
{
public:
    DatabaseHandler();
    void add_receipent(Receipent r);
    void delete_all_receipents();

private:
    SQLite::Database db;
};