#pragma once

#include <vector>
#include <string>
#include <utility>
#include <ctime>
#include <iostream>
#include <optional>
#include <ctime>

#include <nana/gui.hpp>
#include <nana/gui/filebox.hpp>

namespace Util
{
std::string string_to_lower_case(std::string s);
std::vector<std::string> split(const std::string &s, char delim);
bool string_ends_with(const std::string &str, const std::string &suffix);
bool string_starts_with(const std::string &str, const std::string &prefix);
std::string get_date_string();
void show_error_message_box(std::string title, std::string text);
void show_info_message_box(std::string title, std::string text);
bool show_confirmation_message_box(std::string title, std::string text);
std::optional<std::string> show_csv_file_selector_box(std::string title);
std::string get_ISO_8601_datetime();
} // namespace Util