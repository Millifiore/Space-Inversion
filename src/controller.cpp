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

    // set the current state of all buttons to be zero upon creation.
    for (auto button: button_map){
        current_button_state[button.first] = 0;
    }
}

Controller::~Controller(){
    SDL_GameControllerClose(instance);
}

void Controller::ProcessButtons(){
    previous_button_state = current_button_state;
    for (auto button: button_map){
        current_button_state[button.first] = SDL_GameControllerGetButton(instance, button.second);
    }
}

bool Controller::GetButtonPressed(string button){
    return current_button_state[button];
}

bool Controller::GetButtonWasPressed(string button){
    return !previous_button_state[button] && current_button_state[button];
}

vector<double> Controller::GetAnalogStick(string stick){
    double x = SDL_GameControllerGetAxis(instance, analog_map[stick][0]) / 32767;
    double y = SDL_GameControllerGetAxis(instance, analog_map[stick][1]) / 32767;
    return {x, y};
}

double Controller::GetTrigger(string trigger){
    return SDL_GameControllerGetAxis(instance, trigger_map[trigger]) / 32767; 
}

void Controller::SetRumble(double left_motor, double right_motor, double seconds){
    SDL_GameControllerRumble(instance, (left_motor/100) * 65535, (right_motor/100) * 65535, (seconds) * 1000);
}


ControllerManager::ControllerManager(){
    cout << SDL_NumJoysticks() << endl;
    for(int i = 0; i < SDL_NumJoysticks(); i++){
        if (i >= 4){break;}
        controllers.push_back(new Controller(i));
        number_of_controllers += 1;
    }
}

ControllerManager::~ControllerManager(){
    for (int i = 0; i < number_of_controllers; i++){
        delete controllers[i];
    }
}

void ControllerManager::ProcessControllerEvents(SDL_Event * event){
    if (event->type == SDL_CONTROLLERDEVICEADDED){
        controllers.push_back(new Controller(event->cdevice.which));
        number_of_controllers += 1;
    }
    
    else if (event->type == SDL_CONTROLLERDEVICEREMOVED) {
        for (int i = 0; i < number_of_controllers; i++){
            if (controllers[i]->instance_id == event->cdevice.which){
                delete controllers[i];
                controllers.erase(controllers.begin()+i);
                number_of_controllers -= 1;
                break;
            }
        }
    }
}

void ControllerManager::ProcessControllerButtonState(){
    for (auto controller: controllers){
        controller->ProcessButtons();
    }
}

bool ControllerManager::GetControllerButtonPressed(int i, string button){
    if ((0 <= i) && (i <= number_of_controllers-1)){
        return controllers[i]->GetButtonPressed(button);
    }
    return false;
}

bool ControllerManager::GetControllerButtonWasPressed(int i, string button){
    if ((0 <= i) && (i <= number_of_controllers-1)){
        return controllers[i]->GetButtonWasPressed(button);
    }
    return false;
}

void ControllerManager::SetControllerRumble(int i, double left_motor, double right_motor, double seconds){
    if ((0 <= i) && (i <= number_of_controllers-1)){
        return controllers[i]->SetRumble(left_motor, right_motor, seconds);
    }
}
