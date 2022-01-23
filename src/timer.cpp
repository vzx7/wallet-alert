#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include "headers/timer.h"

using namespace std;

void Timer::setTimeout(auto function, int delay)
{
    active = true;
    thread t([=]()
             {
        if(!active.load()) return;
        this_thread::sleep_for(chrono::seconds(delay));
        if(!active.load()) return;
        function(); });
    t.detach();
}

void Timer::setInterval(auto function, int interval)
{
    active = true;
    thread t([=]()
             {
        while(active.load()) {
            this_thread::sleep_for(chrono::seconds(interval));
            if(!active.load()) return;
            function();
        } });
    t.detach();
}

void Timer::stop()
{
    active = false;
}