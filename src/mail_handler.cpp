#include "mail_handler.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-qualifiers"
#pragma GCC diagnostic ignored "-Wunused-value"
#include <SMTPClient.h>
#pragma GCC diagnostic pop

#include <string>

using namespace std;

MailHandler::MailHandler(string host, int port, string username, string passwd)
    : SMTPClient{[](const std::string &) { return; }}
{
    SMTPClient.InitSession(host + ":" + to_string(port), username, passwd,
                           CMailClient::SettingsFlag::ALL_FLAGS,
                           CMailClient::SslTlsFlag::ENABLE_TLS);
}

MailHandler::MailHandler() : SMTPClient{[](const std::string &) { return; }}
{
}

void MailHandler::init_session(string host, int port, string username, string passwd)
{
    SMTPClient.InitSession(host + ":" + to_string(port), username, passwd,
                           CMailClient::SettingsFlag::ALL_FLAGS,
                           CMailClient::SslTlsFlag::ENABLE_TLS);
}

bool MailHandler::send_email(string sender, string receiver, string subject, string text)
{
    string strMail = "Subject: " + subject + "\n\n" + text + "\n";
    return SMTPClient.SendString("<" + sender + ">", "<" + receiver + ">", "", strMail);
}