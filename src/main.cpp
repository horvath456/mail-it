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
#include "new_job_form.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-qualifiers"
#pragma GCC diagnostic ignored "-Wunused-value"
#include <SMTPClient.h>
#pragma GCC diagnostic pop

using namespace std;
using namespace Util;

int main()
{
    CSMTPClient SMTPClient{[](const std::string &str) { cerr << str << endl; }};
    SMTPClient.InitSession("smtp.office365.com:587", "Horvath.Andreas@student.htlwrn.ac.at", "",
                           CMailClient::SettingsFlag::ALL_FLAGS,
                           CMailClient::SslTlsFlag::ENABLE_TLS);
    bool res = SMTPClient.SendString("<Horvath.Andreas@student.htlwrn.ac.at>", "<mail@andreas-horvath.at>", "", "Subject: Test\n\nHallo\n");
    if (res)
        cout << "JAA" << endl;
    else
        cout << "NEIN" << endl;

    DatabaseHandler db{};
    MailHandler mailer{};
    MainForm main_form{};

    try
    {
        if (db.get_config())
        {
            Config cfg{db.get_config().value()};
            mailer.init_session(cfg.host, cfg.port, cfg.username, cfg.passwd);
        }
    }
    catch (exception &e)
    {
        cerr << e.what() << endl;
        show_error_message_box("Fehler", "Beim Lesen der Konfiguration ist ein Fehler aufgetreten.");
        return -1;
    }

    auto delete_all_receipents = [&]() {
        if (!show_confirmation_message_box("Bestätigung", "Wollen Sie wirklich alle Receipents löschen?"))
        {
            return;
        }
        try
        {
            db.delete_all_receipents();
            show_info_message_box("Löschen erfolgreich", "Es wurden alle Receipents gelöscht.");
        }
        catch (exception &e)
        {
            cerr << e.what() << endl;
            show_error_message_box("Fehler", "Beim Löschen der Receipents ist ein Fehler aufgetreten.");
        }
    };

    auto import_receipents = [&]() {
        optional<string> filename = show_csv_file_selector_box("Receipents-CSV-Datei auswählen");
        if (!filename)
        {
            return;
        }

        try
        {
            db.delete_all_receipents();
        }
        catch (exception &e)
        {
            cerr << e.what() << endl;
            show_error_message_box("Fehler", "Beim Löschen der Receipents ist ein Fehler aufgetreten.");
            return;
        }

        try
        {
            vector<Receipent> receipents = CSV::read_receipent_list(filename.value());
            for (const Receipent &r : receipents)
            {
                db.add_receipent(r);
            }
            show_info_message_box("Importieren erfolgreich", "Es wurden " + to_string(receipents.size()) + " Receipents importiert.");
        }
        catch (exception &e)
        {
            cerr << e.what() << endl;
            show_error_message_box("Fehler", "Beim Importieren der Receipents ist ein Fehler aufgetreten.");
        }
    };

    auto new_job = [&]() {
        Config cfg;
        if (db.get_config())
        {
            cfg = db.get_config().value();
        }

        NewJobForm new_job_form{cfg.tmplate};
        nana::API::modal_window(new_job_form.handle());

        if (!new_job_form.saved())
        {
            return;
        }

        Job job = new_job_form.get_value();

        try
        {
            db.add_job(job);
            main_form.update_listbox(db.get_all_jobs());
        }
        catch (invalid_argument &e)
        {
            if (string{e.what()} == "Job with that name already exists")
            {
                show_error_message_box("Fehler", "Ein Job mit diesem Namen existiert bereits.");
            }
            else
            {
                show_error_message_box("Fehler", "Beim Erstellen des Jobs ist ein Fehler aufgetreten.");
            }
        }
        catch (exception &e)
        {
            cerr << e.what() << endl;
            show_error_message_box("Fehler", "Beim Erstellen des Jobs ist ein Fehler aufgetreten.");
        }
    };

    auto email_cfg = [&]() {
        Config cfg;
        if (db.get_config())
        {
            cfg = db.get_config().value();
        }

        EmailConfigInputbox email_cfg{main_form, cfg.host, cfg.port, cfg.username, cfg.passwd};
        bool res = email_cfg.show();
        if (!res)
        {
            return;
        }

        cfg.host = email_cfg.get_host();
        cfg.port = email_cfg.get_port();
        cfg.username = email_cfg.get_username();
        cfg.passwd = email_cfg.get_password();

        try
        {
            db.set_config(cfg);
        }
        catch (exception &e)
        {
            cerr << e.what() << endl;
            show_error_message_box("Fehler", "Beim Schreiben der Konfiguration ist ein Fehler aufgetreten.");
        }

        mailer.init_session(cfg.host, cfg.port, cfg.username, cfg.passwd);
    };

    auto template_cfg = [&]() {
        Config cfg;
        if (db.get_config())
        {
            cfg = db.get_config().value();
        }

        TemplateConfigForm cfg_form{cfg.tmplate};
        nana::API::modal_window(cfg_form.handle());

        if (!cfg_form.saved())
        {
            return;
        }

        cfg.tmplate = cfg_form.get_value();

        try
        {
            db.set_config(cfg);
        }
        catch (exception &e)
        {
            cerr << e.what() << endl;
            show_error_message_box("Fehler", "Beim Schreiben der Konfiguration ist ein Fehler aufgetreten.");
        }
    };

    auto send_job = [&](Job job) {
        optional<string> filename = show_csv_file_selector_box("Jobfile auswählen");
        if (!filename)
        {
            return;
        }

        try
        {
            stringstream ss;
            bool success = true;

            string email_sender = db.get_config().value_or(Config{}).username;

            unsigned int counter = 0;
            unsigned int successful_counter = 0;
            unsigned int unsuccessful_counter = 0;

            JobSender::send_job(job, filename.value(), db.get_all_receipents(),
                                [&](string email_receiver, string subject, string email_contents) {
                                    ss << "From: <" << email_sender << ">\n";
                                    ss << "To: <" << email_receiver << ">\n";
                                    ss << "Subject: " << subject << "\n\n";
                                    ss << email_contents;
                                    ss << "\n\n\n";

                                    counter++;

                                    bool email_send_success = mailer.send_email(email_sender, email_receiver, subject, email_contents);
                                    if (!email_send_success)
                                    {
                                        success = false;
                                        unsuccessful_counter++;
                                    }
                                    else
                                    {
                                        successful_counter++;
                                    }
                                });

            if (!success)
            {
                show_error_message_box("Fehler", "Das Versenden der Emails war nicht erfolgreich. Es wurden " +
                                                     to_string(successful_counter) + " von " + to_string(counter) + " Emails versandt.");
            }
            else
            {
                ofstream myfile;
                myfile.open(job.get_jobname() + "_sent.log");
                myfile << ss.str();
                myfile.close();

                job.set_datetime(get_ISO_8601_datetime());
                db.update_job_datetime(job);
                main_form.update_listbox(db.get_all_jobs());
            }
        }
        catch (exception &e)
        {
            cerr << e.what() << endl;
            show_error_message_box("Fehler", "Beim Versenden des Jobs ist ein Fehler aufgetreten.");
        }
    };

    auto simulate_send_job = [&](Job job) {
        optional<string> filename = show_csv_file_selector_box("Jobfile auswählen");
        if (!filename)
        {
            return;
        }

        try
        {
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
        }
        catch (exception &e)
        {
            cerr << e.what() << endl;
            show_error_message_box("Fehler", "Beim Simulieren des Versendens des Jobs ist ein Fehler aufgetreten.");
        }
    };

    auto delete_job = [&](Job job) {
        try
        {
            db.delete_job(job);
            main_form.remove_selection();
            main_form.update_listbox(db.get_all_jobs());
        }
        catch (exception &e)
        {
            cerr << e.what() << endl;
            show_error_message_box("Fehler", "Beim Löschen des Jobs ist ein Fehler aufgetreten.");
        }
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
    nana::API::window_size(main_form, {750, 450});

    nana::exec();

    return 0;
}
