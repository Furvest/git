#include "manager.hpp"
#include "testscene.hpp"
#include "titlescene.hpp"
#include <memory>
void Manager::Init() {
    SDL_Init(SDL_INIT_VIDEO);
    char* game_dir_cstr = SDL_GetCurrentDirectory();
    game_dir = game_dir_cstr;
    SDL_free(game_dir_cstr);
    w = SDL_CreateWindow("hi!", 1280, 720, SDL_WINDOW_RESIZABLE);
    r = SDL_CreateRenderer(w, nullptr);
    SDL_SetRenderVSync(r, 1);
    g_Renderer.Init(r);
    g_TexManager.Init(r);
    SDL_ShowWindow(w);
    SDL_SetRenderLogicalPresentation(r, 1920, 1080, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    sceneManager.SceneList.push_back(std::make_unique<TitleScene>());
}
void Manager::Render() {
    sceneManager.Render(delta);
    SDL_RenderPresent(r);
};
void Manager::Update() {
    bool no_scenes_left=sceneManager.RemoveQueued();
    uint64_t ticks = SDL_GetTicks();
    delta = (float)(ticks - prev_ticks) / 1000.0f;
    
    SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
    SDL_RenderClear(r);

    SDL_Event event_holder;
    char event_desc_buf[10240];
    while (SDL_PollEvent(&event_holder)) {

        SDL_ConvertEventToRenderCoordinates(r, &event_holder);
        SDL_GetEventDescription(&event_holder, event_desc_buf, sizeof(event_desc_buf));
        printf("event info: ");
        printf("%s\n",event_desc_buf);

        if(event_holder.type== SDL_EVENT_QUIT ||
           event_holder.type == SDL_EVENT_KEY_DOWN && event_holder.key.key == SDLK_ESCAPE) {
            Shutdown();
            return;
        };
        sceneManager.HandleEvent(&event_holder);
    };
    sceneManager.Update(delta);
    prev_ticks = SDL_GetTicks();
    if (no_scenes_left) {
        Shutdown();
        return;
    };
    Render();

};
void Manager::Shutdown() {
    DidQuit = true;
//    g.Deinit();
    SDL_DestroyWindow(w);
    SDL_Quit();
};
