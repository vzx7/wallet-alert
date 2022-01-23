#include <iostream>
#include <cstdio>
#include <string>
#include "headers/mailer.h"

using namespace std;

class Worker
{
private:
    Mailer mailer;



public:
    void setup(int count, const char *argv[])
    {
        cout << count << endl;
        mailer.set_emails(count, argv);
    }
};