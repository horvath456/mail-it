#include "main_form.h"

#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/menubar.hpp>
#include <nana/gui/widgets/listbox.hpp>
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

    place.bind(*this);
    place.div("vert<menubar weight=28> <listbox>|60vert<inputs weight=20>");
    place.field("menubar") << menubar;
    place.field("listbox") << list;
    place.field("inputs") << tb1;
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