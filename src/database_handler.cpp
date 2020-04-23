#include "database_handler.h"

#include <SQLiteCpp/SQLiteCpp.h>

#include <string>
#include <vector>
#include <optional>
#include <stdexcept>

#include "receipent.h"
#include "job.h"
#include "config.h"

using namespace std;

DatabaseHandler::DatabaseHandler() : db{"database.db3", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE}
{
    db.exec("CREATE TABLE IF NOT EXISTS receipent ("
            "vorname VARCHAR(255),"
            "nachname VARCHAR(255),"
            "email VARCHAR(255),"
            "primary key(vorname, nachname))");
    db.exec("CREATE TABLE IF NOT EXISTS receipent_property ("
            "vorname VARCHAR(255),"
            "nachname VARCHAR(255),"
            "name VARCHAR(255),"
            "value VARCHAR(255),"
            "foreign key(vorname, nachname) references receipent,"
            "primary key(vorname, nachname, name))");
    db.exec("CREATE TABLE IF NOT EXISTS job ("
            "jobname VARCHAR(255),"
            "subject VARCHAR(255),"
            "datetime CHAR(19),"
            "selector TEXT,"
            "template TEXT,"
            "primary key(jobname))");
    db.exec("CREATE TABLE IF NOT EXISTS job_property ("
            "jobname VARCHAR(255) references job,"
            "name VARCHAR(255),"
            "value VARCHAR(255),"
            "primary key(jobname, name))");
    db.exec("CREATE TABLE IF NOT EXISTS config ("
            "host VARCHAR(255),"
            "port NUMBER(5),"
            "username VARCHAR(255),"
            "passwd VARCHAR(255),"
            "template TEXT)");
}

void DatabaseHandler::add_receipent(Receipent r)
{
    db.exec("INSERT INTO receipent VALUES (\"" + r.get_first_name() + "\", \"" +
            r.get_last_name() + "\", \"" + r.get_email() + ")");

    for (auto el : r.get_other_properties())
    {
        db.exec("INSERT INTO receipent_property VALUES (\"" + r.get_first_name() + "\", \"" + r.get_last_name() + "\", \"" +
                el.first + "\", \"" + el.second + "\")");
    }
}

void DatabaseHandler::delete_all_receipents()
{
    db.exec("DELETE FROM receipent");
    db.exec("DELETE FROM receipent_property");
}

vector<Receipent> DatabaseHandler::get_all_receipents()
{
    vector<Receipent> receipents;

    SQLite::Statement query1{db, "SELECT * FROM receipent"};

    while (query1.executeStep())
    {
        Receipent receipent{};

        string firstname = query1.getColumn(0);
        string lastname = query1.getColumn(1);
        string email = query1.getColumn(2);

        receipent.set_email(email);
        receipent.set_last_name(lastname);
        receipent.set_first_name(firstname);

        SQLite::Statement query2{db, "SELECT * FROM receipent_property WHERE vorname = ? AND nachname = ?"};
        query2.bind(1, firstname);
        query2.bind(2, lastname);

        while (query2.executeStep())
        {
            string name = query2.getColumn(2);
            string value = query2.getColumn(3);

            receipent.set_property(name, value);
        }

        receipents.push_back(receipent);
    }

    return receipents;
}

vector<Job> DatabaseHandler::get_all_jobs()
{
    vector<Job> jobs;

    SQLite::Statement query1{db, "SELECT * FROM job"};

    while (query1.executeStep())
    {
        Job job{};

        string jobname = query1.getColumn(0);
        string subject = query1.getColumn(1);
        string datetime = query1.getColumn(2);
        string selector = query1.getColumn(3);
        string tmplate = query1.getColumn(4);

        job.set_datetime(datetime);
        job.set_subject(subject);
        job.set_template(tmplate);
        job.set_selector(selector);
        job.set_jobname(jobname);

        SQLite::Statement query2{db, "SELECT * FROM job_property WHERE jobname = ?"};
        query2.bind(1, jobname);

        while (query2.executeStep())
        {
            string name = query2.getColumn(1);
            string value = query2.getColumn(2);

            job.set_property(name, value);
        }

        jobs.push_back(job);
    }

    return jobs;
}

void DatabaseHandler::add_job(Job j)
{
    if (get_job(j.get_jobname()))
    {
        throw invalid_argument("Job with that name already exists");
    }

    db.exec("INSERT INTO job VALUES (\"" + j.get_jobname() + "\", \"" +
            j.get_subject() + "\", \"" + j.get_datetime() + "\", \"" +
            j.get_selector() + "\", \"" + j.get_template() + "\")");

    for (auto el : j.get_other_properties())
    {
        db.exec("INSERT INTO job_property VALUES (\"" + j.get_jobname() + "\", \"" +
                el.first + "\", \"" + el.second + "\")");
    }
}

void DatabaseHandler::update_job_datetime(Job j)
{
    if (!get_job(j.get_jobname()))
    {
        throw invalid_argument("Job with that name does not exist");
    }

    db.exec("UPDATE job SET datetime=\"" + j.get_datetime() + "\" WHERE jobname=\"" + j.get_jobname() + "\"");
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

        job.set_datetime(datetime);
        job.set_subject(subject);
        job.set_template(tmplate);
        job.set_selector(selector);
        job.set_jobname(jobname);

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

            job.set_property(name, value);
        }

        return job;
    }
    else
    {
        return {};
    }
}

void DatabaseHandler::delete_job(Job j)
{
    db.exec("DELETE FROM job WHERE jobname = \"" + j.get_jobname() + "\"");
    db.exec("DELETE FROM job_property WHERE jobname = \"" + j.get_jobname() + "\"");
}

optional<Config> DatabaseHandler::get_config()
{
    Config cfg{};

    bool found = false;

    SQLite::Statement query{db, "SELECT * FROM config"};

    while (query.executeStep())
    {
        cfg.host = static_cast<string>(query.getColumn(0));
        cfg.port = static_cast<int>(query.getColumn(1));
        cfg.username = static_cast<string>(query.getColumn(2));
        cfg.passwd = static_cast<string>(query.getColumn(3));
        cfg.tmplate = static_cast<string>(query.getColumn(4));

        found = true;
    }

    if (found)
    {
        return cfg;
    }
    else
    {
        return {};
    }
}

void DatabaseHandler::set_config(Config cfg)
{
    db.exec("UPDATE config SET host = \"" + cfg.host + "\", port = " + to_string(cfg.port) +
            ", username = \"" + cfg.username + "\", passwd = \"" + cfg.passwd +
            "\", template = \"" + cfg.tmplate + "\"");
}