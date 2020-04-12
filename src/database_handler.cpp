#include "database_handler.h"

#include <SQLiteCpp/SQLiteCpp.h>

#include <string>
#include <optional>

#include "receipent.h"
#include "job.h"

using namespace std;

DatabaseHandler::DatabaseHandler() : db{"database.db3", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE}
{
    db.exec("CREATE TABLE IF NOT EXISTS receipent ("
            "class VARCHAR(10),"
            "firstname VARCHAR(255),"
            "lastname VARCHAR(255),"
            "username VARCHAR(255),"
            "password VARCHAR(255),"
            "email VARCHAR(255),"
            "id VARCHAR(255),"
            "primary key(firstname, lastname)) ");
    db.exec("CREATE TABLE IF NOT EXISTS job ("
            "jobname VARCHAR(255),"
            "subject VARCHAR(255),"
            "datetime CHAR(19),"
            "selector TEXT,"
            "template TEXT,"
            "primary key(jobname)) ");
    db.exec("CREATE TABLE IF NOT EXISTS job_property ("
            "jobname VARCHAR(255) references job,"
            "name VARCHAR(255),"
            "value VARCHAR(255),"
            "primary key(jobname, name)) ");
}

void DatabaseHandler::add_receipent(Receipent r)
{
    string class_str{r.hasKey("class") ? "\"" + r.get_value("class") + "\"" : "NULL"};
    string username_str{r.hasKey("username") ? "\"" + r.get_value("username") + "\"" : "NULL"};
    string password_str{r.hasKey("password") ? "\"" + r.get_value("password") + "\"" : "NULL"};
    string id_str{r.hasKey("id") ? "\"" + r.get_value("id") + "\"" : "NULL"};

    db.exec("INSERT INTO receipent VALUES (\"" + class_str + "\", \"" +
            r.get_first_name().value + "\", \"" + r.get_last_name().value + "\", " + username_str + ", " +
            password_str + ", \"" + r.get_email().value + "\"," + id_str + ")");
}

void DatabaseHandler::delete_all_receipents()
{
    db.exec("DELETE FROM receipent");
}

void DatabaseHandler::add_job(Job j)
{
    db.exec("INSERT INTO job VALUES (\"" + j.get_jobname().value + "\", \"" +
            j.get_subject().value + "\", \"" + j.get_datetime().value + "\", \"" +
            j.get_selector().value + "\", \"" + j.get_template().value + "\")");

    for (auto el : j.get_other_properties())
    {
        db.exec("INSERT INTO job_property VALUES (\"" + j.get_jobname().value + "\", \"" +
                el.first + "\", \"" + el.second.value + "\")");
    }
}

optional<Job> DatabaseHandler::get_job(string jobname)
{
    Job job{};

    bool found = false;

    SQLite::Statement query1{db, "SELECT * FROM job WHERE jobname = ?"};
    query1.bind(1, jobname);

    while (query1.executeStep())
    {
        string jobname = query1.getColumn(0);
        string subject = query1.getColumn(1);
        string datetime = query1.getColumn(2);
        string selector = query1.getColumn(3);
        string tmplate = query1.getColumn(4);

        job.properties["jobname"] = jobname;
        job.properties["subject"] = subject;
        job.properties["datetime"] = datetime;
        job.properties["selector"] = selector;
        job.properties["template"] = tmplate;

        found = true;
    }

    if (found)
    {
        SQLite::Statement query2{db, "SELECT * FROM job_property WHERE jobname = ?"};
        query2.bind(1, jobname);

        while (query2.executeStep())
        {
            string name = query2.getColumn(1);
            string value = query2.getColumn(2);

            job.properties[name] = value;
        }

        return job;
    } else return {};
}

void DatabaseHandler::delete_job(Job j)
{
    db.exec("DELETE FROM job WHERE jobname = \"" + j.get_jobname().value + "\"");
    db.exec("DELETE FROM job_property WHERE jobname = \"" + j.get_jobname().value + "\"");
}