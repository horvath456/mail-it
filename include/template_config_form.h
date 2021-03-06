#pragma once

#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/place.hpp>
#include <string>

class TemplateConfigForm : public nana::form
{
public:
    TemplateConfigForm(std::string tmplate);
    bool saved();
    std::string get_value();

private:
    bool save_clicked = false;
    std::string value;
    nana::place place;
    nana::textbox tb_template;
    nana::button btn_save;
};