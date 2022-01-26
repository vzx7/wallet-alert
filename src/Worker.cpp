#include <iostream>
#include <cstdio>
#include <string>
#include "headers/Mailer.h"

using namespace std;

class Worker
{
private:
    Mailer mailer;



public:
    void setup(int count, const char *argv[])
    {
        mailer.setEmails(count, argv);
    }
};