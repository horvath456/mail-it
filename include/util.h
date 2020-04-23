
#pragma once

#include <vector>
#include <string>
#include <utility>
#include <ctime>
#include <iostream>

std::string string_to_lower_case(std::string s)
{
    std::string res{};

    for (char c : s)
    {
        res += tolower(c);
    }

    return res;
}

std::vector<std::string> split(const std::string &s, char delim)
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

bool string_ends_with(const std::string &str, const std::string &suffix)
{
    return str.size() >= suffix.size() && 0 == str.compare(str.size() - suffix.size(), suffix.size(), suffix);
}

bool string_starts_with(const std::string &str, const std::string &prefix)
{
    return str.size() >= prefix.size() && 0 == str.compare(0, prefix.size(), prefix);
}

std::string get_date_string()
{
    time_t curr_time;
    tm *curr_tm;
    char date_string[100];

    time(&curr_time);
    curr_tm = localtime(&curr_time);

    strftime(date_string, 50, "%B %d, %Y", curr_tm);

    return std::string{date_string};
}