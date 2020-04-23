#include "util.h"

#include <vector>
#include <string>
#include <utility>
#include <ctime>
#include <iostream>
#include <optional>
#include <ctime>

#include <nana/gui.hpp>
#include <nana/gui/filebox.hpp>

std::string Util::string_to_lower_case(std::string s)
{
    std::string res{};

    for (char c : s)
    {
        res += tolower(c);
    }

    return res;
}

std::vector<std::string> Util::split(const std::string &s, char delim)
{
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}

bool Util::string_ends_with(const std::string &str, const std::string &suffix)
{
    return str.size() >= suffix.size() && 0 == str.compare(str.size() - suffix.size(), suffix.size(), suffix);
}

bool Util::string_starts_with(const std::string &str, const std::string &prefix)
{
    return str.size() >= prefix.size() && 0 == str.compare(0, prefix.size(), prefix);
}

std::string Util::get_date_string()
{
    time_t curr_time;
    tm *curr_tm;
    char date_string[100];

    time(&curr_time);
    curr_tm = localtime(&curr_time);

    strftime(date_string, 50, "%B %d, %Y", curr_tm);

    return std::string{date_string};
}

void Util::show_error_message_box(std::string title, std::string text)
{
    nana::msgbox mb{0, title, nana::msgbox::ok};
    mb.icon(mb.icon_error);
    mb << text;
    mb.show();
}

void Util::show_info_message_box(std::string title, std::string text)
{
    nana::msgbox mb{0, title, nana::msgbox::ok};
    mb.icon(mb.icon_information);
    mb << text;
    mb.show();
}

bool Util::show_confirmation_message_box(std::string title, std::string text)
{
    nana::msgbox mb{0, title, nana::msgbox::yes_no};
    mb.icon(mb.icon_question);
    mb << text;
    return mb.show() == nana::msgbox::pick_yes;
}

std::optional<std::string> Util::show_csv_file_selector_box(std::string title)
{
    nana::filebox fb(0, true);
    fb.add_filter(("CSV File"), ("*.csv"));
    fb.add_filter(("All Files"), ("*.*"));
    fb.title(title);

    auto files = fb();
    if (!files.empty())
    {
        std::string file = files.front().string();
        return file;
    }
    else
    {
        return std::nullopt;
    }
}

std::string Util::get_ISO_8601_datetime()
{
    time_t now;
    time(&now);
    char buf[sizeof "2011-10-08T07:07:09Z"];
    strftime(buf, sizeof buf, "%FT%TZ", gmtime(&now));
    return std::string{buf};
}