#include "game.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <string>
#include "anm2data.hpp"
#include "manager.hpp"
#include "fs.hpp"


void Game::Init() {
    printf("initting game\n");
    test_tex.path = std::string(SDL_GetBasePath())+"assets/test_texture.png";
    test_tex.texture = g_TexManager.GetTexture(test_tex.path);
    test_spr.Load(FSManager::GetAssetPath() + "slop.anm2");
    test_spr.state.anim_name = "Shocked";
};

void Game::Render() {
    SDL_SetRenderDrawColor(g_Manager.r, 64, 64, 64, 255);
    SDL_RenderClear(g_Manager.r);
//    SDL_FRect src = SDL_FRect{ 0,0,512,512 };
//    counter += 1;
//   src.x = 50.0f*sin(0.001f*(float)counter);
//    g_Renderer.Render(test_tex.texture, Vector(src.x, src.y), Quad(0, 0, 256, 512), Vector(0, 0), Vector(1, 1), src.x);
    test_spr.Render(Vector(500, 500));
    if (counter % 4 == 0) {
        test_spr.Update();
    };
    counter++;
};

void Game::Deinit() {
    g_TexManager.FreeTexture(test_tex.path);
    test_tex.path = "";
    test_tex.texture = nullptr;
};

