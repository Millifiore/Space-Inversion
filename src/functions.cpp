#include "functions.h"

void ShowError(char * title, string message, string log, bool show_sdl_error){
        string error_string = "";
        if (show_sdl_error){
            error_string = SDL_GetError();
        }
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, (message + error_string).c_str(), NULL);
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, (log + error_string).c_str());
}

