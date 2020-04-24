#include "button_inline_widget.h"

#include <nana/gui.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/listbox.hpp>

#pragma GCC diagnostic ignored "-Wunused-parameter"

using namespace nana;

void ButtonInlineWidget::create(window wd)
{
    btn_.create(wd);
    btn_.caption("Löschen");
    btn_.events().click([this] {
        auto &lsbox = dynamic_cast<listbox &>(indicator_->host());
        lsbox.erase(lsbox.at(pos_));
    });
    btn_.events().mouse_move([this] {
        indicator_->hovered(pos_);
    });
}

void ButtonInlineWidget::activate(inline_indicator &ind, index_type pos)
{
    indicator_ = &ind;
    pos_ = pos;
}

void ButtonInlineWidget::notify_status(status_type status, bool status_on)
{
}

void ButtonInlineWidget::resize(const nana::size &dimension)
{
    auto sz = dimension;
    btn_.size(sz);
}

void ButtonInlineWidget::set(const value_type &value)
{
}

bool ButtonInlineWidget::whether_to_draw() const
{
    return false;
}
