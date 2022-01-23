#ifndef WALLET_ALERT_MILER_H
#define WALLET_ALERT_MILER_H

class Mailer
{
public:
    void set_emails(int count, const char *argv[]);
    void send_alert();
};

#endif //WALLET_ALERT_MILER_H