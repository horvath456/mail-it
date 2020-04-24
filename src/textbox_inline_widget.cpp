#include "textbox_inline_widget.h"

#include <nana/gui.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/listbox.hpp>

#pragma GCC diagnostic ignored "-Wunused-parameter"

using namespace nana;

void TextboxInlineWidget::create(window wd)
{
    txt_.create(wd);
    txt_.events().click([this] {
        //Select the item when clicks the textbox
        indicator_->selected(pos_);
    });

    txt_.events().mouse_move([this] {
        //Highlight the item when hovers the textbox
        indicator_->hovered(pos_);
    });

    txt_.events().key_char([this](const arg_keyboard &arg) {
        if (arg.key == keyboard::enter)
        {
            //Modify the item when enter is pressed
            arg.ignore = true;
            indicator_->modify(pos_, txt_.caption());
        }
    });
}

void TextboxInlineWidget::activate(inline_indicator &ind, index_type pos)
{
    indicator_ = &ind;
    pos_ = pos;
}

void TextboxInlineWidget::notify_status(status_type status, bool status_on)
{
}

void TextboxInlineWidget::resize(const nana::size &dimension)
{
    auto sz = dimension;
    txt_.size(sz);
    rectangle r(sz.width + 5, 0, 45, sz.height);
}

void TextboxInlineWidget::set(const value_type &value)
{
    txt_.caption(value);
}

bool TextboxInlineWidget::whether_to_draw() const
{
    return false;
}