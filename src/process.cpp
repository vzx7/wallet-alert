#include <iostream>
#include "timer.cpp"
#include <fstream>
#include <cstdio>
#include <string>

using namespace std;

class Process
{
private:
    Timer timer;

    /**
     * @brief Stop program execution
     *
     * @return int
     */
    int kill_wallet_alert()
    {
        string pid;
        string file_path = "./PID";
        ifstream file;

        file.open(file_path);
        if (!file)
        {
            throw "ERROR: The file was not opened!";
            return 1;
        }

        getline(file, pid);

        if (pid.empty())
        {
            file.close();
            throw "ERROR: PID was not found!";
            return 1;
        }

        string command = "kill " + pid;

        int is_kill = system(command.c_str());

        if (is_kill != 0)
        {
            file.close();
            throw "ERROR: The program has not been stopped!";
            return 1;
        }

        file.close();

        if (remove(file_path.c_str()) != 0)
        {
            throw "ERROR: Файл содержащий PID не был удален!";
            return 1;
        }

        return 0;
    };

public:
    void run()
    {
        int interval = 5;
        timer.setInterval([&]()
                          { cout << "Hey.. After each " << interval << "s..." << endl; },
                          interval); // 3600

        cout << "Start proccess" << endl;

        while (true)
            ;
    }

    void stop()
    {
        if (kill_wallet_alert() != 0)
        {
            cout << "ERROR: The program has not been stopped!" << endl;
        }
    }
};