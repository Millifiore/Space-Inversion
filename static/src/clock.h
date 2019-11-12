#pragma once
#include "headers.h"

class Clock{
    public:
        double delta_time_s;
        double delta_time;
        Clock();
        void Tick();
        ~Clock();
       
    private:
        Uint64 last_time;
        Uint64 current_time;
};