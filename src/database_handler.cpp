#include "database_handler.h"

#include <SQLiteCpp/SQLiteCpp.h>
#include <string>

using namespace std;

DatabaseHandler::DatabaseHandler() : db{"database.db3", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE}
{
    db.exec("CREATE TABLE IF NOT EXISTS receipents ("
            "class VARCHAR(10),"
            "firstname VARCHAR(255),"
            "lastname VARCHAR(255),"
            "username VARCHAR(255),"
            "password VARCHAR(255),"
            "email VARCHAR(255),"
            "id VARCHAR(255),"
            "primary key(firstname, lastname)) ");
}

void DatabaseHandler::add_receipent(Receipent r)
{
    string class_str{r.hasKey("class") ? "\"" + r.properties["class"].value + "\"" : "NULL"};
    string username_str{r.hasKey("username") ? "\"" + r.properties["username"].value + "\"" : "NULL"};
    string password_str{r.hasKey("password") ? "\"" + r.properties["password"].value + "\"" : "NULL"};
    string id_str{r.hasKey("id") ? "\"" + r.properties["id"].value + "\"" : "NULL"};

    db.exec("INSERT INTO receipents VALUES (" + class_str + ", \"" +
            r.get_first_name().value + "\", \"" + r.get_last_name().value + "\", " + username_str + ", " +
            password_str + ", \"" + r.get_email().value + "\"," + id_str + ", ) ");
}

void DatabaseHandler::delete_all_receipents()
{
    db.exec("DELETE FROM receipents");
}