#pragma GCC diagnostic ignored "-Wdeprecated-copy"

#include "main_form.h"

#include <functional>
#include <utility>
#include <string>
#include <vector>
#include <iostream>

#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/menubar.hpp>
#include <nana/gui/widgets/listbox.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/basic_types.hpp>
#include <nana/gui/place.hpp>

#include "job.h"

using namespace nana;
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
    std::string jobname;
    orr >> jobname;
    job.set_jobname(jobname);
    return orr;
}

MainForm::MainForm()
{
    caption("mit - Mail It");

    menubar.create(*this);
    make_menus();

    all_jobs_listbox.create(*this);
    all_jobs_listbox.append_header("Jobname");
    all_jobs_listbox.enable_single(true, false);
    all_jobs_listbox.events().selected([&]() {
        if (all_jobs_listbox.selected().size() > 0)
        {
            int item = all_jobs_listbox.selected().at(0).item;
            Job job;
            string jobname = all_jobs_listbox.at(0).at(item).text(0);
            for (Job j : all_jobs)
            {
                if (j.get_jobname() == jobname)
                {
                    job = j;
                }
            }
            selected_job = job;
            is_job_selected = true;
            tb_jobname.reset(job.get_jobname());
            tb_subject.reset(job.get_subject());
            tb_template.reset(job.get_template());
            tb_selector.reset(job.get_selector());
            btn_send.enabled(selected_job.get_datetime() == "");
            btn_simulate_send.enabled(true);
            btn_delete_job.enabled(true);
        }
        else
        {
            selected_job = {};
            is_job_selected = false;
            tb_jobname.reset("");
            tb_subject.reset("");
            tb_template.reset("");
            tb_selector.reset("");
            btn_send.enabled(false);
            btn_simulate_send.enabled(false);
            btn_delete_job.enabled(false);
        }
    });

    tb_jobname.create(*this);
    tb_jobname.editable(false);
    tb_jobname.tip_string("Jobname:").multi_lines(false);

    tb_subject.create(*this);
    tb_subject.editable(false);
    tb_subject.tip_string("Subject:").multi_lines(false);

    tb_datetime.create(*this);
    tb_datetime.editable(false);
    tb_datetime.tip_string("Versendedatum:").multi_lines(false);

    tb_template.create(*this);
    tb_template.editable(false);
    tb_template.tip_string("Template:").multi_lines(true);

    tb_selector.create(*this);
    tb_selector.editable(false);
    tb_selector.tip_string("Selector:").multi_lines(true);

    btn_simulate_send.create(*this);
    btn_simulate_send.caption("Senden simulieren");
    btn_simulate_send.events().click([this]() {
        simulate_send_job(selected_job);
    });
    btn_simulate_send.enabled(false);

    btn_send.create(*this);
    btn_send.caption("Job senden");
    btn_send.events().click([this]() {
        send_job(selected_job);
    });
    btn_send.enabled(false);

    btn_delete_job.create(*this);
    btn_delete_job.caption("Job löschen");
    btn_delete_job.events().click([this]() {
        delete_job(selected_job);
    });
    btn_delete_job.enabled(false);

    place.bind(*this);
    place.div("vert<menubar weight=28> <<listbox>|60%<vertical <vertical gap=10 margin=10 textboxs arrange=[25,25,25]><weight=45 gap=10 margin=10 buttons>>>");
    place.field("menubar") << menubar;
    place.field("listbox") << all_jobs_listbox;
    place.field("textboxs") << tb_jobname;
    place.field("textboxs") << tb_subject;
    place.field("textboxs") << tb_datetime;
    place.field("textboxs") << tb_template;
    place.field("textboxs") << tb_selector;
    place.field("buttons") << btn_simulate_send;
    place.field("buttons") << btn_send;
    place.field("buttons") << btn_delete_job;
    place.collocate();
}

void MainForm::make_menus()
{
    menubar.push_back("&Jobs");
    menubar.push_back("&Receipents");
    menubar.push_back("&Konfiguration");
    menubar.at(0).append("Neuer Job", [this](menu::item_proxy &) {
        new_job();
    });
    menubar.at(1).append("Alle löschen", [this](menu::item_proxy &) {
        delete_all_receipents();
    });
    menubar.at(1).append("Importieren", [this](menu::item_proxy &) {
        import_receipents();
    });
    menubar.at(2).append("Email-Zugangsdaten", [this](menu::item_proxy &) {
        email_cfg();
    });
    menubar.at(2).append("Default-Template", [this](menu::item_proxy &) {
        template_cfg();
    });
}

void MainForm::set_delete_all_receipents_function(std::function<void()> f)
{
    delete_all_receipents = f;
}

void MainForm::set_import_receipents_function(std::function<void()> f)
{
    import_receipents = f;
}

void MainForm::set_new_job_function(std::function<void()> f)
{
    new_job = f;
}

void MainForm::set_email_cfg_function(std::function<void()> f)
{
    email_cfg = f;
}

void MainForm::set_template_cfg_function(std::function<void()> f)
{
    template_cfg = f;
}

void MainForm::set_send_job_function(std::function<void(Job job)> f)
{
    send_job = f;
}

void MainForm::set_simulate_send_job_function(std::function<void(Job job)> f)
{
    simulate_send_job = f;
}

void MainForm::set_delete_job_function(std::function<void(Job job)> f)
{
    delete_job = f;
}

void MainForm::update_listbox(std::vector<Job> jobs)
{
    all_jobs_listbox.auto_draw(false);
    all_jobs_listbox.clear();
    for (auto &job : jobs)
    {
        all_jobs_listbox.at(0).append(job);
    }
    all_jobs_listbox.auto_draw(true);
    all_jobs = jobs;

    tb_jobname.reset(selected_job.get_jobname());
    tb_subject.reset(selected_job.get_subject());
    tb_template.reset(selected_job.get_template());
    tb_selector.reset(selected_job.get_selector());

    if (is_job_selected)
    {
        btn_send.enabled(selected_job.get_datetime() == "");
        btn_simulate_send.enabled(true);
        btn_delete_job.enabled(true);
    }
    else
    {
        btn_send.enabled(false);
        btn_simulate_send.enabled(false);
        btn_delete_job.enabled(false);
    }
}

void MainForm::remove_selection()
{
    is_job_selected = false;
    selected_job = {};
    tb_jobname.reset("");
    tb_subject.reset("");
    tb_template.reset("");
    tb_selector.reset("");
    btn_send.enabled(false);
    btn_simulate_send.enabled(false);
    btn_delete_job.enabled(false);
}