#include <stdio.h>
#include "game/manager.hpp"

Manager g_Manager;
int main(int argc, char* argv[]){
    g_Manager.Init();
    while (!g_Manager.IsShutdown()) {
        g_Manager.Update();
    };
    return 0;
};