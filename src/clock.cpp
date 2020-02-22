#include "clock.h"

Clock::Clock(){
    delta_time = 0;
    delta_time_s = 0;
    last_time = 0;
    current_time = SDL_GetTicks();
}

void Clock::Tick(){
    last_time = current_time;
    current_time = SDL_GetTicks();
    // delta time is the time between the first and last frame, used to have accurate timing.
    delta_time = (current_time - last_time);
    // converts delta time, which is in milleseconds, into how it is in seconds. so if delta was 1ms, here it'd be .001 second.
    delta_time_s = (delta_time * .001); 
}

Clock::~Clock(){}