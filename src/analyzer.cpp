#include <fstream>
#include <iostream>
#include <string>
#include "headers/mailer.h"

using namespace std;

class Analyzer
{
private:
    Mailer mailer;
    int checkBalance(string currency)
    {
        cout << "Check " << currency << " address balance..." << endl;
        string file_path = "./resource/" + currency;
        ifstream file;

        file.open(file_path);
        if (!file)
        {
            throw "ERROR: The file currency list was not opened!";
        }
        string address;
        while (getline(file, address))
        {
            cout << address << endl;
        }
        return 1;
    };

public:
    int compareBalance()
    {
        checkBalance("BTC");
        return 1;
    };
};