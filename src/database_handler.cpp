#include "database_handler.h"

#include <SQLiteCpp/SQLiteCpp.h>

DatabaseHandler::DatabaseHandler()
{
    SQLite::Database db("database.db3", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
}
