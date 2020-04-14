#pragma once

#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/menubar.hpp>
#include <nana/gui/widgets/listbox.hpp>
#include <nana/gui/place.hpp>

class MainForm : public nana::form
{
public:
    MainForm();

private:
    void make_menus();
    nana::place place;
    nana::menubar menubar;
    nana::listbox list;
};