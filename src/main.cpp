#include <iostream>

#include "config.h"
#include "job.h"
#include "receipent.h"

#include "database_handler.h"
#include "mail_handler.h"
#include "csv_utils.h"

#include "main_form.h"

using namespace std;


int main()
{
    MailHandler mailer{"host", 443, "user", "pw"};
    DatabaseHandler db{};

    MainForm main_form;
    main_form.show();
    nana::exec();

    return 0;
}
