#pragma once

#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/menubar.hpp>
#include <nana/gui/widgets/listbox.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/place.hpp>

class MainForm : public nana::form
{
public:
    MainForm();

private:
    void make_menus();

public:
    nana::place place;
    nana::menubar menubar;
    nana::listbox list;
    nana::textbox tb1;
    nana::textbox tb2;
    nana::button btn1;
    nana::button btn2;
};