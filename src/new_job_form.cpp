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

    tb_jobname.create(*this);
    tb_jobname.tip_string("Jobname:").multi_lines(false);

    tb_subject.create(*this);
    tb_subject.tip_string("Subject:").multi_lines(false);

    tb_template.create(*this);
    tb_template.tip_string("Template:").multi_lines(true);
    tb_template.reset(tmplate);

    tb_selector.create(*this);
    tb_selector.tip_string("Selector:").multi_lines(true);

    btn_create.create(*this);
    btn_create.caption("Anlegen");

    place.bind(*this);
    place.div("<vertical <vertical gap=10 margin=10 textboxs arrange=[25,25]><weight=45 gap=10 margin=10 buttons>>");
    place.field("textboxs") << tb_jobname;
    place.field("textboxs") << tb_subject;
    place.field("textboxs") << tb_template;
    place.field("textboxs") << tb_selector;
    place.field("buttons") << btn_create;
    place.collocate();
}