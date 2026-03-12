#include "game.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <string>
#include "anm2.hpp"
void Manager::Init() {
    SDL_Init(SDL_INIT_VIDEO);
    char* game_dir_cstr = SDL_GetCurrentDirectory();
    game_dir = game_dir_cstr;
    SDL_free(game_dir_cstr);
    w = SDL_CreateWindow("hi!", 960, 540, 0);
    SDL_ShowWindow(w);
}
void Manager::Update() {
    SDL_PollEvent(&event_holder);
    if (event_holder.type == SDL_EVENT_KEY_DOWN && event_holder.key.key == 'c') {
        Shutdown();
        return;
    };
};
void Manager::Shutdown() {
    DidQuit = true;
    SDL_DestroyWindow(w);
    SDL_Quit();
};