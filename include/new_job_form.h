#pragma once

#include <string>

#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/listbox.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/place.hpp>

#include "job.h"

class NewJobForm : public nana::form
{
public:
    NewJobForm(std::string tmplate);
    bool saved();
    Job get_value();

private:
    void set_job_value();

    bool save_clicked = false;
    Job job;
    nana::place place;
    nana::listbox job_properties_listbox;
    nana::textbox tb_jobname;
    nana::textbox tb_subject;
    nana::textbox tb_template;
    nana::textbox tb_selector;
    nana::button btn_create;
    nana::button btn_add_property;
};