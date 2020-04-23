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

using namespace nana;
using namespace std;

TemplateConfigForm::TemplateConfigForm()
{
    caption("Template-Konfiguration");

    tb1.create(*this);
    tb1.tip_string("Template:").multi_lines(true);

    btn1.create(*this);
    btn1.caption("Speichern");

    place.bind(*this);
    place.div("vert<<textboxs margin=10 gap=10 weight=28><buttons margin=10>>");
    place.field("textboxs") << tb1;
    place.field("buttons") << btn1;
    place.collocate();
}