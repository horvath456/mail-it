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

    list.create(*this);
    list.append_header("Jobname");
    list.enable_single(true, false);
    list.events().selected([&]() {
        if (list.selected().size() > 0)
        {
            int item = list.selected().at(0).item;
            Job job;
            string jobname = list.at(0).at(item).text(0);
            for (Job j : all_jobs)
            {
                if (j.get_jobname() == jobname)
                {
                    job = j;
                }
            }
            selected_job = job;
            tb1.reset(job.get_jobname());
            tb2.reset(job.get_subject());
            tb3.reset(job.get_template());
            tb4.reset(job.get_selector());
        }
        else
        {
            selected_job = {};
        }
    });

    tb1.create(*this);
    tb1.tip_string("Jobname:").multi_lines(false);

    tb2.create(*this);
    tb2.tip_string("Subject:").multi_lines(false);

    tb3.create(*this);
    tb3.tip_string("Template:").multi_lines(true);

    tb4.create(*this);
    tb4.tip_string("Selector:").multi_lines(true);

    btn1.create(*this);
    btn1.caption("Senden simulieren");
    btn1.events().click([this]() {
        send_job(selected_job);
    });

    btn2.create(*this);
    btn2.caption("Job senden");
    btn2.events().click([this]() {
        simulate_send_job(selected_job);
    });

    btn3.create(*this);
    btn3.caption("Job löschen");
    btn3.events().click([this]() {
        delete_job(selected_job);
    });

    place.bind(*this);
    place.div("vert<menubar weight=28> <<listbox>|60%<vertical <vertical gap=10 margin=10 textboxs arrange=[25,25]><weight=45 gap=10 margin=10 buttons>>>");
    place.field("menubar") << menubar;
    place.field("listbox") << list;
    place.field("textboxs") << tb1;
    place.field("textboxs") << tb2;
    place.field("textboxs") << tb3;
    place.field("textboxs") << tb4;
    place.field("buttons") << btn1;
    place.field("buttons") << btn2;
    place.field("buttons") << btn3;
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
    list.auto_draw(false);
    for (auto &job : jobs)
    {
        list.at(0).append(job);
    }
    list.auto_draw(true);
    all_jobs = jobs;

    tb1.reset(selected_job.get_jobname());
    tb2.reset(selected_job.get_subject());
    tb3.reset(selected_job.get_template());
    tb4.reset(selected_job.get_selector());
}