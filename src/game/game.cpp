#include "game.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <string>
#include "anm2data.hpp"
#include "manager.hpp"
#include "fs.hpp"


void Game::Init() {
    printf("initting game\n");
    test_spr.Load(R"(C:\SteamLibrary\steamapps\common\The Binding of Isaac Rebirth\extracted_resources\resources\gfx\cutscenes\intro.anm2)");
//    test_spr.Load(FSManager::GetAssetPath() + "slop.anm2");
//    test_spr.state.anim_name = "Shocked";
//    test_spr.state.cur_frame = 3500;
}
void Game::Update()
{};

void Game::Render() {
    uint64_t ticks = SDL_GetTicks();
    float delta = (float)(ticks - prev_ticks) / 1000.0f;
    int w, h;
    SDL_SetRenderDrawColor(g_Manager.r, 64, 64, 64, 255);
    SDL_RenderClear(g_Manager.r);
    g_Renderer.globalScale = 4.0f;
    SDL_GetRenderOutputSize(g_Manager.r, &w, &h);
    test_spr.Render(Vector((double)w / (2.0 * g_Renderer.globalScale), (double)h / (2.0 * g_Renderer.globalScale)));
    test_spr.Update(delta);
    counter++;
    SDL_RenderDebugText(g_Manager.r, 250, 250, "hi!");
    prev_ticks = SDL_GetTicks();
};

void Game::ProcessClick(Vector click_pos)
{};

void Game::Deinit() {
    g_TexManager.FreeTexture(test_tex.path);
    test_tex.path = "";
    test_tex.texture = nullptr;
};

