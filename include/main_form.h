#pragma once

#include <functional>
#include <utility>

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
    MainForm(std::function<void()>, std::function<void()>);

private:
    void make_menus();
    std::function<void()> delete_all_receipents;
    std::function<void()> import_receipents;

public:
    nana::place place;
    nana::menubar menubar;
    nana::listbox list;
    nana::textbox tb1;
    nana::textbox tb2;
    nana::button btn1;
    nana::button btn2;
};