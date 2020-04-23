#include "email_config_inputbox.h"

#include <nana/gui.hpp>
#include <string>

using namespace nana;
using namespace std;

EmailConfigInputbox::EmailConfigInputbox(form frm) : inbox{frm, "Bitte die Email-Zugangsdaten eingeben.", "Email-Zugangsdaten"},
                                           host{"Host"},
                                           port{"Port", 0, 0, 65535, 1},
                                           username{"Username"},
                                           password{"Passwort"}

{
    //Sets a verifier
    inbox.verify([this](window handle) {
        if (host.value().empty())
        {
            msgbox mb(handle, "Ungültige Eingabe");
            mb << "Bitte Host angeben.";
            mb.show();
            return false;
        }
        if (port.value() > 65535 || port.value() < 0)
        {
            msgbox mb(handle, "Ungültige Eingabe");
            mb << "Bitte Port angeben.";
            mb.show();
            return false;
        }
        if (username.value().empty())
        {
            msgbox mb(handle, "Ungültige Eingabe");
            mb << "Bitte Username angeben.";
            mb.show();
            return false;
        }
        if (password.value().empty())
        {
            msgbox mb(handle, "Ungültige Eingabe");
            mb << "Bitte Passwort angeben.";
            mb.show();
            return false;
        }
        return true;
    });
}

bool EmailConfigInputbox::show()
{
    return inbox.show(host, port, username, password);
}

string EmailConfigInputbox::get_host()
{
    return host.value();
}

int EmailConfigInputbox::get_port()
{
    return port.value();
}

string EmailConfigInputbox::get_username()
{
    return username.value();
}

string EmailConfigInputbox::get_password()
{
    return password.value();
}