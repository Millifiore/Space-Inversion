#!/bin/bash

em++ -O3 --preload-file resources -g src/*.cpp -std=c++17 -s ALLOW_MEMORY_GROWTH=1 -s MODULARIZE=1 -s USE_SDL=2 -s USE_SDL_MIXER=2 -s USE_SDL_TTF=2 -s WASM=1 -o static/SpaceInversion.js

