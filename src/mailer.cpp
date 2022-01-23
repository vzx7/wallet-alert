#include <fstream>
#include <iostream>

using namespace std;

class Mailer
{
public:
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
    };

    void send_alert()
    {
    }
};