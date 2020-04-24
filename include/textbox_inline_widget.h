#pragma once

#include <nana/gui.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/listbox.hpp>

class TextboxInlineWidget : public nana::listbox::inline_notifier_interface
{
    inline_indicator *indicator_{nullptr};
    index_type pos_;
    nana::textbox txt_;

private:
    void create(nana::window wd) override;
    void activate(inline_indicator &ind, index_type pos) override;
    void notify_status(status_type status, bool status_on);
    void resize(const nana::size &dimension) override;
    void set(const value_type &value) override;
    bool whether_to_draw() const override;
};