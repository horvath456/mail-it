#pragma once

#include <string>

struct Config
{
    Config() : host{"smtp.office365.com"}, port{587}, username{}, passwd{}, tmplate{}
    {
    }

    std::string host;
    int port;
    std::string username;
    std::string passwd;
    std::string tmplate;
};