#pragma once

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-qualifiers"
#pragma GCC diagnostic ignored "-Wunused-value"
#include <SMTPClient.h>
#pragma GCC diagnostic pop

#include <string>

class MailHandler
{
public:
    MailHandler(std::string host, int port, std::string username, std::string passwd);
    MailHandler();
    void init_session(std::string host, int port, std::string username, std::string passwd);
    bool send_email(std::string sender, std::string receiver, std::string subject, std::string text);

private:
    CSMTPClient SMTPClient;
};