#include <iostream>

#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>

#include <nlohmann/json.hpp>
#include <inja.hpp>

#include "config.h"
#include "job.h"
#include "receipent.h"

#include "database_handler.h"
#include "mail_handler.h"
#include "csv_utils.h"

using namespace std;
using namespace nana;
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


    form fm;

    label lb{fm, rectangle{10, 10, 100, 100}};
    lb.caption("Hello, world!");

    fm.show();

    exec();
}
