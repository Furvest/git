#include "game.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <string>
#include "anm2.hpp"

TextureManager g_TexManager;
void TextureManager::Init(SDL_Renderer* renderer)
{
    r = renderer;
}
SDL_Texture* TextureManager::GetTexture(const std::string& path) {
     for (TexEntry tex : tex_list) {
        if (tex.path == path) {
            tex.refcount += 1;
            return tex.texture;
        };
    };
    SDL_Surface* s = SDL_LoadPNG(path.c_str());
    if (!s) { return nullptr; };
    SDL_Texture* t = SDL_CreateTextureFromSurface(r, s);
    printf("%s\n", SDL_GetError());
    TexEntry e;
    e.path = path;
    e.refcount = 1;
    e.texture = t;
    SDL_DestroySurface(s);
    tex_list.push_back(e);
    return e.texture;
};

void TextureManager::FreeTexture(const std::string& path) {
    for (TexEntry tex : tex_list) {
        if (tex.path == path) {
            tex.refcount -= 1;
        };
    };
};

void TextureManager::TrimTextures() {
    for (TexEntry tex : tex_list) {
        if (tex.refcount <= 0 && tex.texture) {
            SDL_DestroyTexture(tex.texture);
            tex.texture = nullptr;
            tex.path = "";
        };
    };
};

void Game::Init() {
    test_tex.path = std::string(SDL_GetBasePath())+"test_texture.png";
    test_tex.texture = g_TexManager.GetTexture(test_tex.path);
};

void Game::Render() {
    SDL_RenderClear(g_Manager.r);
    SDL_FRect src = SDL_FRect{ 0,0,512,512 };
    counter += 1;
    src.x = 50*sin(counter*0.001);
    SDL_RenderTexture(g_Manager.r, test_tex.texture, nullptr, &src);
};

void Game::Deinit() {
    g_TexManager.FreeTexture(test_tex.path);
    test_tex.path = "";
    test_tex.texture = nullptr;
};

void Manager::Init() {
    SDL_Init(SDL_INIT_VIDEO);
    char* game_dir_cstr = SDL_GetCurrentDirectory();
    game_dir = game_dir_cstr;
    SDL_free(game_dir_cstr);
    w = SDL_CreateWindow("hi!", 960, 540, 0);
    SDL_ShowWindow(w);
    r=SDL_CreateRenderer(w, nullptr);
    g_TexManager.Init(r);
    g.Init();
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
