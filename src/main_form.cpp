#include "main_form.h"

#include <functional>
#include <utility>

#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/menubar.hpp>
#include <nana/gui/widgets/listbox.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/basic_types.hpp>
#include <nana/gui/place.hpp>

using namespace nana;

MainForm::MainForm()
{
    caption("mit - Mail It");

    menubar.create(*this);
    make_menus();

    list.create(*this);
    list.append_header("Jobname");

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

    btn2.create(*this);
    btn2.caption("Job senden");

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