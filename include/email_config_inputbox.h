#pragma once

#include <nana/gui.hpp>
#include <string>

class EmailConfigInputbox
{
public:
    EmailConfigInputbox(nana::form frm, std::string host_v, int port_v, std::string username_v, std::string password_v);
    bool show();
    std::string get_host();
    int get_port();
    std::string get_username();
    std::string get_password();

private:
    nana::form frm;

    nana::inputbox inbox;

    nana::inputbox::text host;
    nana::inputbox::integer port;
    nana::inputbox::text username;
    nana::inputbox::text password;
};