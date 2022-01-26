#ifndef WALLET_ALERT_MILER_H
#define WALLET_ALERT_MILER_H
#include <iostream>

class Mailer
{
public:
    void setEmails(int count, const char *argv[]);
    /**
     * Send alert email
     * @param text
     */
    void sendAlert(std::string text);
};

#endif //WALLET_ALERT_MILER_H