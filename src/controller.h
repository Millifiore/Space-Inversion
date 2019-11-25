#pragma once
#include "headers.h"

class Controller {
    private:
        map<string, SDL_GameControllerButton> button_map;
        map<string, SDL_GameControllerAxis> trigger_map;
        map<string, vector<SDL_GameControllerAxis>> analog_map;
        map<string, int> current_button_state;
        map<string, int> previous_button_state;
    public:
        SDL_GameController * instance;
        SDL_JoystickID instance_id;
        Controller(int);
        ~Controller();

        void ProcessButtons();
        bool GetButtonPressed(string);
        bool GetButtonWasPressed(string);
        vector<double> GetAnalogStick(string);
        double GetTrigger(string);

        // The values for the left motor and the right motor are up to 100.
        void SetRumble(double left, double right, double seconds);

};

class ControllerManager {
    private:
        vector<Controller *> controllers;
        int number_of_controllers = 0;
    
    public:
        ControllerManager();
        ~ControllerManager();

        void ProcessControllerEvents(SDL_Event *);
        void ProcessControllerButtonState();
        bool GetControllerButtonPressed(int, string);
        bool GetControllerButtonWasPressed(int, string);

        void SetControllerRumble(int, double, double, double);

};