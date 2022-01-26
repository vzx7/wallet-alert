#include <iostream>
#include <string>
#include "Process.cpp"
#include "Worker.cpp"

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

int main(int argc, const char *argv[])
{
    Process *process = new Process();
    Worker *worker = new Worker();
    Mode mode;
    string inst = "!!!***!!!\nThe program must be called with at least one argument - \"mode\".\nRequired argument - \"mode\" was not passed!\nRun the program with an argument: mode=start or mode=stop.\n!!!***!!!";

    if (argc < 2)
    {
        cout << inst << endl;
        return 1;
    }

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

    try
    {
        switch (mode)
        {
        case START:
        {
            worker->setup(argc - 2, argv);
            process->run();
        }
        break;

        case STOP:
        {
            process->stop();
        }
        break;
        }
    }
    catch (const char *msg)
    {
        cerr << msg << endl;
        return 1;
    }

    delete process;
    delete worker;
    return 0;
}
