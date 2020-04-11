#include "main_form.h"

#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/menubar.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/msgbox.hpp>
#include <nana/gui/filebox.hpp>

using namespace nana;

MainForm::MainForm()
{
    caption("mit - Mail It");
    menubar_.create(*this);

    textbox_.create(*this);
    textbox_.borderless(true);
    API::effects_edge_nimbus(textbox_, effects::edge_nimbus::none);
    textbox_.enable_dropfiles(true);

    _m_make_menus();

    place_.bind(*this);
    place_.div("vert<menubar weight=28><textbox>");
    place_.field("menubar") << menubar_;
    place_.field("textbox") << textbox_;
    place_.collocate();
}

void MainForm::_m_make_menus()
{
    menubar_.push_back("&FILE");
    menubar_.at(0).append("New", [this](menu::item_proxy &) {

    });
    menubar_.at(0).append("Open", [this](menu::item_proxy &) {

    });
    menubar_.at(0).append("Save", [this](menu::item_proxy &) {

    });
}