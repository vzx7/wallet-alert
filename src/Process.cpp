#include <iostream>
#include <cstdio>
#include <string>
#include "Analyzer.cpp"
#include "headers/Timer.h"
#include "headers/FileService.h"

using namespace std;

class Process
{
private:
    Timer timer;
    Analyzer *analyzer = new Analyzer();

    /**
     * @brief Save the process PID of this application to a file named 'PID' in the application's directory.
     *
     * @return int
     */
    int savePID()
    {
        string errmsg = "ERROR: The PID has not been saved!";
        try
        {
            int is_pid = system("ps aux | grep wallet_alert | tr -s ' ' | cut -d ' ' -f 2 | head  -n1 > $HOME/wallet_alert/resources/PID");

            if (is_pid != 0)
            {
                throw errmsg;
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
     * @brief Stop program execution
     *
     * @return int
     */
    int killWalletAlert()
    {

        FileService fileService("PID");
        string pid = fileService.readFile();

        if (pid.empty()) {
            fileService.closeFile();
            throw "PID NOT FOUND";
        }

        string command = "kill " + pid;

        int is_kill = system(command.c_str());

        if (is_kill != 0)
        {
            fileService.closeFile();
            throw "ERROR: The program has not been stopped!";
        }

        fileService.closeFile();
        fileService.removeFile("PID");

        return 0;
    };

public:
    void run()
    {
        int interval = 3;
        timer.setInterval([&]()
                          { 
                            cout << "Hey.. After each " << interval << "s..." << endl; 
                            bool isDone = analyzer->compareBalance();
                                if (isDone) {
                                    stop();
                                }
                            },
                          interval); // 3600

        cout << "Start process" << endl;

        while (true)
            ;
    }

    void stop()
    {
        if (savePID() != 0)
        {
            cout << "ERROR: The PID has not been saved!" << endl;
            return;
        }
        delete analyzer;

        if (killWalletAlert() != 0)
        {
            cout << "ERROR: The program has not been stopped!" << endl;
        }
    }
};