#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>

using namespace std;

class Worker
{
private:
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

    /**
     * @brief Set the emails object
     *
     * @param count Number of devoted addresses
     * @param argv Address array
     */
    void set_emails(int count, const char *argv[])
    {
        if (count == 0)
        {
            cout << "New distribution addresses were not transferred!";
            return;
        }

        cout << "New mailing list (" << count << " addresses) sent, old addresses will be deleted!" << endl;

        string file_path = "./resource/addresses";
        ofstream file;

        file.open(file_path, ios::out);
        if (!file)
        {
            throw "ERROR: The file was not opened!";
        }

        string arr[count];
        int i = 1;
        while (i <= count)
        {
            file << argv[i] << endl;
            i += 1;
        }

        cout << "The new mailing list has been saved..." << endl;
        file.close();
    }

public:
    void setup(int count, const char *argv[])
    {
        if (save_PID() != 0)
        {
            cout << "ERROR: The PID has not been saved!" << endl;
        }

        set_emails(count, argv);
    }
};