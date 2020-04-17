#include "main_form.h"

#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/menubar.hpp>
#include <nana/gui/widgets/listbox.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/button.hpp>
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
    tb1.tip_string("User:").multi_lines(false);

    tb2.create(*this);
    tb2.tip_string("Password:").multi_lines(true);

    btn1.create(*this);
    btn2.create(*this);

    place.bind(*this);
    place.div("vert<menubar weight=28> <<listbox>|50<vertical <vertical gap=10 textboxs arrange=[25,25]><weight=25 gap=10 buttons>>>");
    place.field("menubar") << menubar;
    place.field("listbox") << list;
    place.field("textboxs") << tb1;
    place.field("textboxs") << tb2;
    place.field("buttons") << btn1;
    place.field("buttons") << btn2;
    place.collocate();
}

void MainForm::make_menus()
{
    menubar.push_back("&FILE");
    menubar.at(0).append("New", [this](menu::item_proxy &) {

    });
    menubar.at(0).append("Open", [this](menu::item_proxy &) {

    });
    menubar.at(0).append("Save", [this](menu::item_proxy &) {

    });
}