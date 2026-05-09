#include "manager.hpp"
void Manager::Init() {
    SDL_Init(SDL_INIT_VIDEO);
    char* game_dir_cstr = SDL_GetCurrentDirectory();
    game_dir = game_dir_cstr;
    SDL_free(game_dir_cstr);
    w = SDL_CreateWindow("hi!", 1280, 800, SDL_WINDOW_RESIZABLE);
    r = SDL_CreateRenderer(w, nullptr);
    SDL_SetRenderVSync(r, 1);
    g_Renderer.Init(r);
    g_TexManager.Init(r);
    g.Init();
    SDL_ShowWindow(w);
}
void Manager::Render() {
    g.Render();
    SDL_RenderPresent(r);
};
void Manager::Update() {
    Render();
    SDL_Event event_holder;
    SDL_PollEvent(&event_holder);
    if (event_holder.type == SDL_EVENT_KEY_DOWN && event_holder.key.key == 'c') {
        Shutdown();
        return;
    };
};
void Manager::Shutdown() {
    DidQuit = true;
    g.Deinit();
    SDL_DestroyWindow(w);
    SDL_Quit();
};
