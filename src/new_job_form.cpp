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

    nana::API::window_size(handle(), {450, 350});

    job_properties_listbox.create(*this);
    job_properties_listbox.append_header("Eigenschaftsname", 150);
    job_properties_listbox.append_header("Eigenschaftswert", 150);
    job_properties_listbox.enable_single(true, false);

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
    btn_create.events().click([this]() {
        save_clicked = true;
        close();
    });

    place.bind(*this);
    place.div("<vertical <vertical gap=10 margin=10 textboxs arrange=[25,25]><weight=45 gap=10 margin=10 buttons>>");
    place.field("textboxs") << tb_jobname;
    place.field("textboxs") << tb_subject;
    place.field("textboxs") << tb_template;
    place.field("textboxs") << tb_selector;
    place.field("textboxs") << job_properties_listbox;
    place.field("buttons") << btn_create;
    place.collocate();
}

bool NewJobForm::saved()
{
    return save_clicked;
}

Job NewJobForm::get_value()
{
    Job job{};
    job.set_jobname(tb_jobname.text());
    job.set_selector(tb_selector.text());
    job.set_template(tb_template.text());
    job.set_subject(tb_subject.text());
    return job;
}