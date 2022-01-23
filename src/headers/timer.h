#pragma once
#include <atomic>
#include <iostream>

class Timer
{
    std::atomic<bool> active{true};

public:
    void setTimeout(auto function, int delay);
    void setInterval(auto function, int interval);
    void stop();
};
