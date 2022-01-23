#pragma once

class Mailer
{
public:
    void set_emails(int count, const char *argv[]);
    void send_alert();
};