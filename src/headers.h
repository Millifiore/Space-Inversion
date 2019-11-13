#pragma once
//SDL2 Includes
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
//Standard Includes
#include <fstream>
#include <iostream>
#include <string.h>
#include <sstream>
#include <vector>
#include <memory>
#include <map>
#include <algorithm>
#include <ctime>
#include <cstdlib>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

//Game Includes
#include "clock.h"
#include "keyboard.h"
#include "mouse.h"


using namespace std; 