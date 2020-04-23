#pragma once

#include <functional>
#include <utility>

#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/menubar.hpp>
#include <nana/gui/widgets/listbox.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/place.hpp>

class MainForm : public nana::form
{
public:
    MainForm();

    void set_delete_all_receipents_function(std::function<void()>);
    void set_import_receipents_function(std::function<void()>);
    void set_new_job_function(std::function<void()>);
    void set_email_cfg_function(std::function<void()>);
    void set_template_cfg_function(std::function<void()>);

private:
    void make_menus();
    std::function<void()> delete_all_receipents;
    std::function<void()> import_receipents;
    std::function<void()> new_job;
    std::function<void()> email_cfg;
    std::function<void()> template_cfg;

public:
    nana::place place;
    nana::menubar menubar;
    nana::listbox list;
    nana::textbox tb1;
    nana::textbox tb2;
    nana::textbox tb3;
    nana::textbox tb4;
    nana::button btn1;
    nana::button btn2;
    nana::button btn3;
};