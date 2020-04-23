#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <utility>

#pragma GCC diagnostic ignored "-Wdeprecated-copy"

#include <nana/gui.hpp>
#include <nana/gui/filebox.hpp>

#include "config.h"
#include "job.h"
#include "receipent.h"

#include "database_handler.h"
#include "mail_handler.h"
#include "csv_utils.h"

#include "main_form.h"
#include "config_inputbox.h"

using namespace std;

nana::listbox::oresolver &operator<<(nana::listbox::oresolver &orr, Job &job)
{
    orr << job.get_jobname();
    return orr;
}
std::ostream &operator<<(std::ostream &orr, Job &job)
{
    orr << job.get_jobname();
    return orr;
}
nana::listbox::iresolver &operator>>(nana::listbox::iresolver &orr, Job &job)
{
    string jobname;
    orr >> jobname;
    job.set_jobname(jobname);
    return orr;
}

int main()
{
    DatabaseHandler db{};
    MailHandler mailer{};
    MainForm main_form{};

    if (db.get_config())
    {
        Config cfg{db.get_config().value()};
        mailer.init_session(cfg.host, cfg.port, cfg.username, cfg.passwd);
    }

    auto delete_all_receipents = [&]() {
        db.delete_all_receipents();
    };

    auto import_receipents = [&]() {
        nana::filebox fb(0, true);
        fb.add_filter(("CSV File"), ("*.csv"));
        fb.add_filter(("All Files"), ("*.*"));

        auto files = fb();
        if (!files.empty())
        {
            db.delete_all_receipents();
            string file = files.front().string();
            vector<Receipent> receipents = CSV::read_receipent_list(file);
            for (Receipent &r : receipents)
            {
                db.add_receipent(r);
            }
        }
    };

    auto new_job = [&]() {
        ConfigInputbox cfg_form{main_form};
        cfg_form.show();
    };

    auto email_cfg = [&]() {

    };

    auto template_cfg = [&]() {

    };

    main_form.set_delete_all_receipents_function(delete_all_receipents);
    main_form.set_import_receipents_function(import_receipents);
    main_form.set_new_job_function(new_job);
    main_form.set_email_cfg_function(email_cfg);
    main_form.set_template_cfg_function(template_cfg);

    vector<Job> all_jobs = db.get_all_jobs();
    for (auto &job : all_jobs)
    {
        main_form.list.at(0).append(job);
    }

    main_form.show();
    nana::exec();

    return 0;
}
