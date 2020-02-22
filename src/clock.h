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
        uint32_t last_time;
        uint32_t current_time;
};