#pragma once
#include "headers.h"

class Controller {
    private:
        map<string, SDL_GameControllerButton> button_map;
        map<string, SDL_GameControllerAxis> trigger_map;
        map<string, vector<SDL_GameControllerAxis>> analog_map;
    public:
        SDL_GameController * instance;
        SDL_JoystickID instance_id;
        Controller(int);
        ~Controller();
        bool GetButton(string);
        vector<double> GetAnalogStick(string);
        double GetTrigger(string);
};

class ControllerManager {
    private:
        vector<Controller *> controllers;
    
    public:
        ControllerManager();
        ~ControllerManager();

        void ProcessControllerEvents(SDL_Event *);
        bool GetControllerButton(int, string);
};