#include <iostream>

#include <nlohmann/json.hpp>
#include <inja.hpp>

#include "config.h"
#include "job.h"
#include "receipent.h"

#include "database_handler.h"
#include "mail_handler.h"
#include "csv_utils.h"

#include "main_form.h"

using namespace std;
using namespace inja;
using json = nlohmann::json;

int main()
{
    Config cfg{};
    Job job{};
    Receipent r{};


    MailHandler mailer{"host", 443, "user", "pw"};
    DatabaseHandler db{};


    json data;
    data["name"] = "world";

    render("Hello {{ name }}!", data);               // Returns std::string "Hello world!"


    MainForm main_form;
    main_form.show();
    nana::exec();
}
