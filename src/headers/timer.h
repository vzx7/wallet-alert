//
// Created by zx on 1/24/22.
//
#ifndef WALLET_ALERT_TIMER_H
#define WALLET_ALERT_TIMER_H
#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

using namespace std;
class Timer {
public:
    std::atomic<bool> active{true};
    void setTimeout(auto function, int delay);
    void setInterval(auto function, int interval);
};

void Timer::setTimeout(auto function, int delay) {
    active = true;
    thread t([=]()
             {
                 if(!active.load()) return;
                 this_thread::sleep_for(chrono::seconds(delay));
                 if(!active.load()) return;
                 function();
                 this->active = false;
             });
    t.detach();
}

void Timer::setInterval(auto function, int interval)
{
    active = true;
    thread t([=]()
             {
                cout << "INTERVAL..." << endl;
                 while(active.load()) {
                     this_thread::sleep_for(chrono::seconds(interval));
                     if(!active.load()) return;
                     function();
                 } });
    t.detach();
}


#endif //WALLET_ALERT_TIMER_H