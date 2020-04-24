#include "template_config_form.h"

#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/menubar.hpp>
#include <nana/gui/widgets/listbox.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/basic_types.hpp>
#include <nana/gui/place.hpp>

#include <string>
#include <iostream>

using namespace nana;
using namespace std;

TemplateConfigForm::TemplateConfigForm(string tmplate)
{
    caption("Template-Konfiguration");

    tb_template.create(*this);
    tb_template.tip_string("Template:").multi_lines(true);
    tb_template.reset(tmplate);

    btn_save.create(*this);
    btn_save.caption("Speichern");
    btn_save.events().click([this]() {
        save_clicked = true;
        value = tb_template.text();
        close();
    });

    place.bind(*this);
    place.div("<vertical <textboxs margin=10 gap=10> <buttons margin=10 gap=10 weight=48> >");
    place.field("textboxs") << tb_template;
    place.field("buttons") << btn_save;
    place.collocate();
}

bool TemplateConfigForm::saved()
{
    return save_clicked;
}

string TemplateConfigForm::get_value()
{
    return value;
}