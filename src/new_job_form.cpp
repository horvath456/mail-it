#include "new_job_form.h"

#include <string>

#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/menubar.hpp>
#include <nana/gui/widgets/listbox.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/basic_types.hpp>
#include <nana/gui/place.hpp>

#include "textbox_inline_widget.h"
#include "button_inline_widget.h"

using namespace nana;
using namespace std;

NewJobForm::NewJobForm(string tmplate)
{
    caption("Neuen Job anlegen");

    nana::API::window_size(handle(), {600, 400});

    job_properties_listbox.create(*this);
    job_properties_listbox.append_header("Eigenschaftsname", 150);
    job_properties_listbox.append_header("Eigenschaftswert", 150);
    job_properties_listbox.append_header("Aktion", 70);
    job_properties_listbox.enable_single(true, false);

    job_properties_listbox.at(0).append({"", ""});

    job_properties_listbox.at(0).inline_factory(0, pat::make_factory<TextboxInlineWidget>());
    job_properties_listbox.at(0).inline_factory(1, pat::make_factory<TextboxInlineWidget>());
    job_properties_listbox.at(0).inline_factory(2, pat::make_factory<ButtonInlineWidget>());

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

    btn_add_property.create(*this);
    btn_add_property.caption("Neue Eigenschaft");
    btn_add_property.events().click([this]() {
        job_properties_listbox.at(0).append({"", ""});
    });

    place.bind(*this);
    place.div("<vertical <vertical gap=10 margin=10 textboxs arrange=[25,25]><<gap=10 margin=10 listbox><weight=150 gap=10 margin=10 listbox_btn>><weight=45 gap=10 margin=10 buttons>>");
    place.field("textboxs") << tb_jobname;
    place.field("textboxs") << tb_subject;
    place.field("textboxs") << tb_template;
    place.field("textboxs") << tb_selector;
    place.field("listbox") << job_properties_listbox;
    place.field("listbox_btn") << btn_add_property;
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

    for (auto &entry : job_properties_listbox.at(0))
    {
        string name = entry.text(0);
        string value = entry.text(1);
        job.set_property(name, value);
    }

    return job;
}