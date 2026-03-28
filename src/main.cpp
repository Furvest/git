#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <tinyxml2.h>
#include <string>
#include "game/anm2.hpp"
#include <filesystem>
//#include "game/engine/engine.hpp"
#include "game/game.hpp"

Manager g_Manager;
int     main(int argc, char* argv[]) {
    g_Manager.Init();
    while (!g_Manager.IsShutdown()) {
        g_Manager.Update();
    };
    return 0;
};