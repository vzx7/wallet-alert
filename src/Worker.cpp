#include "headers/Mailer.h"
#include "Process.cpp"

using namespace std;

class Worker
{
private:
    Mailer mailer;
    Process *process = new Process();

public:
    void setup(int count, const char *argv[])
    {
        mailer.setEmails(count, argv);
    }

    void run() {
        process->run();
    }

    void stop() {
        process->stop();
    };

    ~Worker(){
        delete process;
    }
};