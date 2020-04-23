#pragma once

#include <nana/gui.hpp>
#include <string>

class TemplateConfigInputbox
{
public:
    TemplateConfigInputbox(nana::form frm);
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