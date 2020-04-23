#pragma once

#include <functional>
#include <utility>
#include <string>
#include <vector>

#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/menubar.hpp>
#include <nana/gui/widgets/listbox.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/place.hpp>

#include "job.h"

class MainForm : public nana::form
{
public:
    MainForm();

    void set_delete_all_receipents_function(std::function<void()>);
    void set_import_receipents_function(std::function<void()>);
    void set_new_job_function(std::function<void()>);
    void set_email_cfg_function(std::function<void()>);
    void set_template_cfg_function(std::function<void()>);
    void set_send_job_function(std::function<void(Job job)>);
    void set_simulate_send_job_function(std::function<void(Job job)>);
    void set_delete_job_function(std::function<void(Job job)>);

    void update_listbox(std::vector<Job> jobs);

private:
    void make_menus();

    std::vector<Job> all_jobs;
    Job selected_job;

    std::function<void()> delete_all_receipents;
    std::function<void()> import_receipents;
    std::function<void()> new_job;
    std::function<void()> email_cfg;
    std::function<void()> template_cfg;
    std::function<void(Job job)> send_job;
    std::function<void(Job job)> simulate_send_job;
    std::function<void(Job job)> delete_job;

    nana::place place;
    nana::menubar menubar;
    nana::listbox list;
    nana::textbox tb_jobname;
    nana::textbox tb_subject;
    nana::textbox tb_template;
    nana::textbox tb_selector;
    nana::button btn_simulate_send;
    nana::button btn_send;
    nana::button btn_delete_job;
};