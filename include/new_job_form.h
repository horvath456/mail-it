#pragma once

#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/place.hpp>
#include <string>

class NewJobForm : public nana::form
{
public:
    NewJobForm(std::string tmplate);

private:
    nana::place place;
    nana::textbox tb1;
    nana::button btn1;
};