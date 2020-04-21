#include "main_form.h"

#include <functional>
#include <utility>

#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/menubar.hpp>
#include <nana/gui/widgets/listbox.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/place.hpp>

using namespace nana;

MainForm::MainForm(std::function<void()> delete_all_receipents,
                   std::function<void()> import_receipents) : delete_all_receipents{delete_all_receipents},
                                                              import_receipents{import_receipents}
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
    menubar.push_back("&Receipents");
    menubar.at(0).append("Alle löschen", [this](menu::item_proxy &) {
        delete_all_receipents();
    });
    menubar.at(0).append("Importieren", [this](menu::item_proxy &) {
        import_receipents();
    });
}