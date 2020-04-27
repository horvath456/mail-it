#include "send_job.h"

#include <string>
#include <vector>
#include <stdexcept>
#include <functional>
#include <utility>
#include <ctime>
#include <iostream>

#include <nlohmann/json.hpp>
#include <inja.hpp>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreorder"
#pragma GCC diagnostic ignored "-Wdeprecated"
#pragma GCC diagnostic ignored "-Wunused-variable"
#include <csv/reader.hpp>
#pragma GCC diagnostic pop

#include "job.h"
#include "receipent.h"
#include "csv_utils.h"
#include "mail_handler.h"
#include "util.h"

using namespace std;

using namespace inja;
using json = nlohmann::json;

using namespace Util;

Receipent get_receipent(string receipent_name, vector<Receipent> all_receipents)
{
    Receipent return_receipent{};

    string lastname = receipent_name.find(" ") == string::npos ? receipent_name : receipent_name.substr(0, receipent_name.find(" "));
    string firstname = receipent_name.find(" ") == string::npos ? "" : receipent_name.substr(receipent_name.find(" "));

    for (const Receipent &r : all_receipents)
    {
        if (firstname == "")
        {
            if (r.get_last_name() == lastname)
            {
                return r;
            }
        }
        else
        {
            if (string_ends_with(firstname, "."))
            {
                string firstname_without_last_char = firstname.substr(0, firstname.size() - 1);
                if (r.get_last_name() == lastname && string_starts_with(r.get_first_name(), firstname_without_last_char))
                {
                    return r;
                }
            }
            else
            {
                if (r.get_last_name() == lastname && r.get_first_name() == firstname)
                {
                    return r;
                }
            }
        }
    }

    return return_receipent;
}

bool selector_includes_receipent(string selector, Receipent r)
{
    vector<string> tokens = split(selector, '&');

    for (const string &token : tokens)
    {
        vector<string> inner_tokens = split(token, '=');
        string name = string_to_lower_case(inner_tokens.at(0));
        string value = inner_tokens.at(1);

        for (const auto &entry : r.properties)
        {
            string entry_name = string_to_lower_case(entry.first);
            string entry_value = entry.second.value;
            if (entry_name == name && entry_value != value)
            {
                return false;
            }
        }
    }

    return true;
}

void JobSender::send_job(Job job, string jobfile, vector<Receipent> all_receipents, function<void(string, string, string)> send)
{
    csv::Reader reader;
    reader.read(jobfile);

    auto jobfile_contents = reader.rows();

    for (auto &jobfile_el : jobfile_contents)
    {
        if (jobfile_el.find("name") == jobfile_el.end() && jobfile_el.find("Name") == jobfile_el.end())
        {
            throw invalid_argument("Jobfile entry has no name!");
        }

        string receipent_name = jobfile_el.find("name") == jobfile_el.end() ? jobfile_el["Name"] : jobfile_el["name"];
        Receipent r = get_receipent(receipent_name, all_receipents);

        if (!selector_includes_receipent(job.get_selector(), r))
        {
            continue;
        }

        json data;
        for (auto &receipent_prop : r.properties)
        {
            data[string_to_lower_case(receipent_prop.first)] = receipent_prop.second.value;
            data[receipent_prop.first] = receipent_prop.second.value;
        }
        for (auto &job_prop : job.properties)
        {
            data[string_to_lower_case(job_prop.first)] = job_prop.second.value;
            data[job_prop.first] = job_prop.second.value;
        }
        for (auto &jobfile_prop : jobfile_el)
        {
            data[string_to_lower_case(static_cast<string>(jobfile_prop.first))] = static_cast<string>(jobfile_prop.second);
            data[static_cast<string>(jobfile_prop.first)] = static_cast<string>(jobfile_prop.second);
            cout << "Jobfile property: " << (static_cast<string>(jobfile_prop.first)) << " v: " << (static_cast<string>(jobfile_prop.second)) << endl;
        }
        data["date"] = get_date_string();
        data["Date"] = get_date_string();

        string email_contents{render(job.get_template(), data)};
        string email_receiver = r.get_email();
        string subject = job.get_subject();

        send(email_receiver, subject, email_contents);
    }
}
