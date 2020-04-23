#include "new_job_form.h"

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

NewJobForm::NewJobForm(string tmplate)
{
    caption("Neuen Job anlegen");

    tb1.create(*this);
    tb1.tip_string("Template:").multi_lines(true);
    tb1.reset(tmplate);

    btn1.create(*this);
    btn1.caption("Anlegen");

    place.bind(*this);
    place.div("<vertical <textboxs margin=10 gap=10> <buttons margin=10 gap=10 weight=48> >");
    place.field("textboxs") << tb1;
    place.field("buttons") << btn1;
    place.collocate();
}