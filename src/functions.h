#pragma once
#include "headers.h"
#include "scene.h"

// THIS FILE HAS GENERAL FUNCTIONS THAT CAN BE USED THROUGHOUT THE PROGRAM

void ShowError(char * title, string message, string log, bool show_sdl_error);

vector<string> split(string const & word, char delim = ' ');

LevelScene * CreateScene(SpriteCache * cache,Framebuffer * framebuffer , TextCache * ,Player * player, string filepath);