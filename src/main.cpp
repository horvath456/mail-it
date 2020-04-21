#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <utility>

#pragma GCC diagnostic ignored "-Wdeprecated-copy"

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

    if (db.get_config())
    {
        Config cfg{db.get_config().value()};
        mailer.init_session(cfg.host, cfg.port, cfg.username, cfg.passwd);
    }

    auto delete_all_receipents = [&]() {
        db.delete_all_receipents();
    };

    auto import_receipents = [&]() {

    };

    MainForm main_form{delete_all_receipents, import_receipents};

    ConfigInputbox cfg_form{main_form};
    cfg_form.show();

    vector<Job> all_jobs = db.get_all_jobs();

    for (size_t i = 0; i < all_jobs.size(); i++)
    {
        main_form.list.at(i).append(all_jobs.at(i));
    }

    main_form.show();
    nana::exec();

    return 0;
}
