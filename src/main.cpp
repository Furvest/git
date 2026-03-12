#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <tinyxml2.h>
#include <string>
#include "game/anm2.hpp"
#include <filesystem>
//#include "game/engine/engine.hpp"
#include "game/game.hpp"

int main(int argc, char* argv[]){
    Manager m;
    m.Init();
    while (!m.IsShutdown()) {
        m.Update();
    };
    return 0;
};