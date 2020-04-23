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

#pragma GCC diagnostic ignored "-Wunused-parameter"

class TextboxInlineWidget : public listbox::inline_notifier_interface
{
    inline_indicator *indicator_{nullptr};
    index_type pos_;
    textbox txt_;

private:
    void create(window wd) override
    {
        txt_.create(wd);
        txt_.events().click([this] {
            indicator_->selected(pos_);
        });
        txt_.events().mouse_move([this] {
            indicator_->hovered(pos_);
        });
        txt_.events().key_char([this](const arg_keyboard &arg) {
            if (arg.key == keyboard::enter)
            {
                arg.ignore = true;
                indicator_->modify(pos_, txt_.caption());
            }
        });
    }

    void activate(inline_indicator &ind, index_type pos) override
    {
        indicator_ = &ind;
        pos_ = pos;
    }

    void notify_status(status_type status, bool status_on)
    {
    }

    void resize(const nana::size &dimension) override
    {
        auto sz = dimension;
        txt_.size(sz);
        rectangle r(sz.width + 5, 0, 45, sz.height);
    }

    void set(const value_type &value) override
    {
        txt_.caption(value);
    }

    bool whether_to_draw() const override
    {
        return false;
    }
};

class ButtonInlineWidget : public listbox::inline_notifier_interface
{
    inline_indicator *indicator_{nullptr};
    index_type pos_;
    button btn_;

private:
    void create(window wd) override
    {
        btn_.create(wd);
        btn_.caption("Löschen");
        btn_.events().click([this] {
            //Delete the item when button is clicked
            auto &lsbox = dynamic_cast<listbox &>(indicator_->host());
            lsbox.erase(lsbox.at(pos_));
        });
        btn_.events().mouse_move([this] {
            indicator_->hovered(pos_);
        });
    }

    void activate(inline_indicator &ind, index_type pos) override
    {
        indicator_ = &ind;
        pos_ = pos;
    }

    void notify_status(status_type status, bool status_on)
    {
    }

    void resize(const nana::size &dimension) override
    {
        auto sz = dimension;
        btn_.size(sz);
    }

    void set(const value_type &value) override
    {
    }

    bool whether_to_draw() const override
    {
        return false;
    }
};

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
    return job;
}