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
#include "email_config_inputbox.h"
#include "template_config_form.h"

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
        nana::msgbox mb{main_form.handle(), "Bestätigung", nana::msgbox::yes_no};
        mb.icon(mb.icon_question);
        mb << "Wollen Sie wirklich alle Receipents löschen?";
        if (mb.show() == nana::msgbox::pick_yes)
        {
            db.delete_all_receipents();
        }
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
            try
            {
                vector<Receipent> receipents = CSV::read_receipent_list(file);
                for (Receipent &r : receipents)
                {
                    db.add_receipent(r);
                }
                nana::msgbox mb{main_form.handle(), "Importieren erfolgreich", nana::msgbox::ok};
                mb.icon(mb.icon_information);
                mb << "Es wurden " << receipents.size() << " Receipents importiert.";
                mb.show();
            }
            catch (...)
            {
                nana::msgbox mb{main_form.handle(), "Fehler", nana::msgbox::ok};
                mb.icon(mb.icon_error);
                mb << "Beim Importieren der Receipents ist ein Fehler aufgetreten.";
                mb.show();
            }
        }
    };

    auto new_job = [&]() {

    };

    auto email_cfg = [&]() {
        Config cfg;
        if (db.get_config())
        {
            cfg = db.get_config().value();
        }
        EmailConfigInputbox email_cfg{main_form, cfg.host, cfg.port, cfg.username, cfg.passwd};
        if (email_cfg.show())
        {
            cfg.host = email_cfg.get_host();
            cfg.port = email_cfg.get_port();
            cfg.username = email_cfg.get_username();
            cfg.passwd = email_cfg.get_password();
            db.set_config(cfg);
            mailer.init_session(cfg.host, cfg.port, cfg.username, cfg.passwd);
        }
    };

    auto template_cfg = [&]() {
        Config cfg;
        if (db.get_config())
        {
            cfg = db.get_config().value();
        }

        TemplateConfigForm cfg_form{cfg.tmplate};
        cfg_form.show();
        nana::exec();

        if (cfg_form.saved())
        {
            cfg.tmplate = cfg_form.get_value();
            db.set_config(cfg);
        }
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
    nana::API::window_size(main_form, {600, 400});

    nana::exec();

    return 0;
}
