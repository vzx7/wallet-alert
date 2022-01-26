#include <fstream>
#include <iostream>
#include "headers/Mailer.h"

using namespace std;

void Mailer::setEmails(int count, const char *argv[])
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

void Mailer::sendAlert(string text) {
    cout << text << endl;
}
