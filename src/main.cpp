#include <stdio.h>
#include "game/manager.hpp"

Manager g_Manager;

#ifndef ANDROID
int main(int argc, char* argv[]){
    g_Manager.Init();
    while (!g_Manager.IsShutdown()) {
        g_Manager.Update();
    };
    return 0;
};
#endif
#ifdef ANDROID
extern "C"
int SDL_main(int argc, char* argv[]){
    g_Manager.Init();
    SDL_Log("Hello!!!!!!\n");
    while (!g_Manager.IsShutdown()) {
        g_Manager.Update();
    };
    return 0;
};
#endif