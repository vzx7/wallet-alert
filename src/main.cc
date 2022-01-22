#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>

using namespace std;

/**
 * @brief Application start options
 *
 */
enum Mode
{
    START,
    STOP
};

/**
 * @brief Get the Mode object
 *
 * @param arg_mode mode
 * @return Mode
 */
Mode get_mode(string arg_mode)
{
    Mode mode;
    string sMode;
    string delimiter = "=";
    sMode = arg_mode.erase(0, arg_mode.find(delimiter) + 1);

    cout << "Program started correctly: " << sMode << endl;

    if (sMode == "start")
    {
        mode = START;
    }
    else if (sMode == "stop")
    {
        mode = STOP;
    }
    else
    {
        throw "ERROR: Application startup mode is not defined!";
    }

    return mode;
};

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

int main(int argc, const char *argv[])
{
    Mode mode;
    string inst = "!!!***!!!\nThe program must be called with at least one argument - \"mode\".\nRequired argument - \"mode\" was not passed!\nRun the program with an argument: mode=start or mode=stop.\n!!!***!!!";

    if (argc < 2)
    {
        cout << inst << endl;
        return 1;
    }
    else
    {
        try
        {
            mode = get_mode(argv[argc - 1]);
        }
        catch (const char *msg)
        {
            cerr << msg << endl;
            cout << inst << endl;
            return 1;
        }
    }

    try
    {
        switch (mode)
        {
        case START:
        {
            int is_done = save_PID();
            if (is_done != 0)
            {
                cout << "ERROR: The PID has not been saved!" << endl;
            }

            // TODO continue scenario...
        }
        break;

        case STOP:
        {
            if (kill_wallet_alert() != 0)
            {
                cout << "ERROR: The program has not been stopped!" << endl;
            }
        }
        break;
        }
    }
    catch (const char *msg)
    {
        cerr << msg << endl;
        return 1;
    }

    return 0;
}
