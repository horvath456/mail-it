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
        //indicator_->selected(pos_);
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