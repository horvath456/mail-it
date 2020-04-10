#include <iostream>

#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreorder"
#pragma GCC diagnostic ignored "-Wdeprecated"
#pragma GCC diagnostic ignored "-Wunused-variable"
#include <csv/reader.hpp>
#pragma GCC diagnostic pop

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-qualifiers"
#pragma GCC diagnostic ignored "-Wunused-value"
#include <SMTPClient.h>
#pragma GCC diagnostic pop

#include <nlohmann/json.hpp>
#include <inja.hpp>

#include "config.h"
#include "job.h"
#include "receipent.h"
#include "database_handler.h"

using namespace std;
using namespace nana;
using namespace inja;
using json = nlohmann::json;

int main()
{
    Config cfg{};
    Job job{};
    Receipent r{};

    CSMTPClient SMTPClient([](const std::string &) { return; });

    DatabaseHandler db{};

    json data;
    data["name"] = "world";

    render("Hello {{ name }}!", data);               // Returns std::string "Hello world!"
    render_to(std::cout, "Hello {{ name }}!", data); // Prints "Hello world!"

    csv::Reader foo;
    //foo.read("test.csv");

    form fm;

    label lb{fm, rectangle{10, 10, 100, 100}};
    lb.caption("Hello, world!");

    fm.show();

    exec();
}
