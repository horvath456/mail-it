#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <utility>
#include <fstream>
#include <optional>

#include <nana/gui.hpp>
#include <nana/gui/filebox.hpp>

#include "config.h"
#include "job.h"
#include "receipent.h"

#include "database_handler.h"
#include "mail_handler.h"
#include "csv_utils.h"
#include "send_job.h"
#include "util.h"

#include "main_form.h"
#include "email_config_inputbox.h"
#include "template_config_form.h"

using namespace std;
using namespace Util;

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
        if (show_confirmation_message_box("Bestätigung", "Wollen Sie wirklich alle Receipents löschen?"))
        {
            db.delete_all_receipents();
        }
    };

    auto import_receipents = [&]() {
        optional<string> filename = show_csv_file_selector_box();
        if (!filename)
        {
            return;
        }

        db.delete_all_receipents();

        try
        {
            vector<Receipent> receipents = CSV::read_receipent_list(filename.value());
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

    auto send_job = [&](Job job) {
        optional<string> filename = show_csv_file_selector_box();
        if (!filename)
        {
            return;
        }

        stringstream ss;
        bool success = true;

        string email_sender = db.get_config().value_or(Config{}).username;

        JobSender::send_job(job, filename.value(), db.get_all_receipents(),
                            [&](string email_receiver, string subject, string email_contents) {
                                ss << "From: <" << email_sender << ">\n";
                                ss << "To: <" << email_receiver << ">\n";
                                ss << "Subject: " << subject << "\n\n";
                                ss << email_contents;
                                ss << "\n\n\n";

                                bool email_send_success = mailer.send_email(email_sender, email_receiver, subject, email_contents);
                                if (!email_send_success)
                                {
                                    success = false;
                                }
                            });

        if (!success)
        {
            nana::msgbox mb{main_form.handle(), "Fehler", nana::msgbox::ok};
            mb.icon(mb.icon_error);
            mb << "Beim Senden ist ein Fehler aufgetreten.";
            mb.show();
        }
        else
        {
            ofstream myfile;
            myfile.open(job.get_jobname() + "_sent.log");
            myfile << ss.str();
            myfile.close();

            job.set_datetime(get_ISO_8601_datetime());
            db.update_job_datetime(job);
        }
    };

    auto simulate_send_job = [&](Job job) {
        optional<string> filename = show_csv_file_selector_box();
        if (!filename)
        {
            return;
        }

        ofstream myfile;
        myfile.open(job.get_jobname() + "_simulated_sent.log");

        string email_sender = db.get_config().value_or(Config{}).username;

        JobSender::send_job(job, filename.value(), db.get_all_receipents(),
                            [&](string email_receiver, string subject, string email_contents) {
                                myfile << "From: <" << email_sender << ">\n";
                                myfile << "To: <" << email_receiver << ">\n";
                                myfile << "Subject: " << subject << "\n\n";
                                myfile << email_contents;
                                myfile << "\n\n\n";
                            });
        myfile.close();
    };

    auto delete_job = [&](Job job) {
        db.delete_job(job);
        main_form.update_listbox(db.get_all_jobs());
    };

    main_form.set_delete_all_receipents_function(delete_all_receipents);
    main_form.set_import_receipents_function(import_receipents);
    main_form.set_new_job_function(new_job);
    main_form.set_email_cfg_function(email_cfg);
    main_form.set_template_cfg_function(template_cfg);
    main_form.set_send_job_function(send_job);
    main_form.set_simulate_send_job_function(simulate_send_job);
    main_form.set_delete_job_function(delete_job);

    main_form.update_listbox(db.get_all_jobs());

    main_form.show();
    nana::API::window_size(main_form, {700, 400});

    nana::exec();

    return 0;
}
