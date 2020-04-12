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
    list.append_header("Name");
    list.append_header("Age");

    place.bind(*this);
    place.div("vert<menubar weight=28><listbox>");
    place.field("menubar") << menubar;
    place.field("listbox") << list;
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