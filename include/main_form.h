#pragma once

#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/menubar.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/msgbox.hpp>
#include <nana/gui/filebox.hpp>

class MainForm : public nana::form
{
public:
    MainForm();

private:
    void _m_make_menus();
    nana::place place_;
    nana::menubar menubar_;
    nana::textbox textbox_;
};