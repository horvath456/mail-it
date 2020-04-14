#pragma once

#include <SQLiteCpp/SQLiteCpp.h>

#include <optional>
#include <vector>

#include "receipent.h"
#include "job.h"
#include "config.h"

class DatabaseHandler
{
public:
    DatabaseHandler();
    void add_receipent(Receipent r);
    void delete_all_receipents();
    std::vector<Receipent> get_all_receipents();
    std::vector<Job> get_all_jobs();
    void add_job(Job j);
    std::optional<Job> get_job(std::string jobname);
    void delete_job(Job j);
    std::optional<Config> get_config();
    void set_config(Config cfg);

private:
    SQLite::Database db;
};