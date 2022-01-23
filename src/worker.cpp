#include <iostream>
#include <cstdio>
#include <string>
#include "mailer.cpp"

using namespace std;

class Worker
{
private:
    Mailer *mailer = new Mailer();
    /**
     * @brief Save the process PID of this application to a file named 'PID' in the application's directory.
     *
     * @return int
     */
    int save_PID()
    {
        string errmsg = "ERROR: The PID has not been saved!";
        try
        {
            int is_pid = system("ps aux | grep wallet-alert | tr -s ' ' | cut -d ' ' -f 2 | head  -n1 > PID");

            if (is_pid != 0)
            {
                throw errmsg;
                return 1;
            }
        }
        catch (int)
        {
            cout << errmsg << endl;
            return 1;
        }

        return 0;
    };

public:
    void setup(int count, const char *argv[])
    {
        if (save_PID() != 0)
        {
            cout << "ERROR: The PID has not been saved!" << endl;
        }

        mailer->set_emails(count, argv);
    }

    ~Worker()
    {
        delete mailer;
    }
};