#include "controller.h"

Controller::Controller(int i){
    // buttons on a controller
    button_map["A"] = SDL_CONTROLLER_BUTTON_A;
    button_map["B"] = SDL_CONTROLLER_BUTTON_B;
    button_map["X"] = SDL_CONTROLLER_BUTTON_X;
    button_map["Y"] = SDL_CONTROLLER_BUTTON_Y;
    button_map["START"] = SDL_CONTROLLER_BUTTON_START;
    button_map["SELECT"] = SDL_CONTROLLER_BUTTON_GUIDE;
    button_map["LB"] = SDL_CONTROLLER_BUTTON_LEFTSHOULDER;
    button_map["RB"] = SDL_CONTROLLER_BUTTON_RIGHTSHOULDER;

    // dpad buttons
    button_map["UP"]    = SDL_CONTROLLER_BUTTON_DPAD_UP;
    button_map["DOWN"]  = SDL_CONTROLLER_BUTTON_DPAD_DOWN;
    button_map["LEFT"]  = SDL_CONTROLLER_BUTTON_DPAD_LEFT;
    button_map["RIGHT"] = SDL_CONTROLLER_BUTTON_DPAD_RIGHT;

    // trigger values
    trigger_map["LEFT_TRIGGER"]  = SDL_CONTROLLER_AXIS_TRIGGERLEFT;
    trigger_map["RIGHT_TRIGGER"] = SDL_CONTROLLER_AXIS_TRIGGERRIGHT;

    // stick values
    analog_map["LEFT_STICK"] = {SDL_CONTROLLER_AXIS_LEFTX, SDL_CONTROLLER_AXIS_LEFTY};
    analog_map["RIGHT_STICK"] = {SDL_CONTROLLER_AXIS_RIGHTX, SDL_CONTROLLER_AXIS_RIGHTY};


    instance = SDL_GameControllerOpen(i);
    instance_id = SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(instance));
}

Controller::~Controller(){
    SDL_GameControllerClose(instance);
}

bool Controller::GetButton(string button){
    return SDL_GameControllerGetButton(instance, button_map[button]);
}

vector<double> Controller::GetAnalogStick(string stick){
    double x = SDL_GameControllerGetAxis(instance, analog_map[stick][0]) / 32767;
    double y = SDL_GameControllerGetAxis(instance, analog_map[stick][1]) / 32767;
    return {x, y};
}

double Controller::GetTrigger(string trigger){
    return SDL_GameControllerGetAxis(instance, trigger_map[trigger]) / 32767; 
}



ControllerManager::ControllerManager(){}

void ControllerManager::ProcessControllerEvents(SDL_Event * event){
    if (event->type == SDL_CONTROLLERDEVICEADDED){
        controllers.push_back(new Controller(event->cdevice.which));
    }
    
    if (event->type == SDL_CONTROLLERDEVICEREMOVED) {
        for (auto controller: controllers){
            if (controller->instance_id == event->cdevice.which){
                delete controller;
                break;
            }
        }
    }
}