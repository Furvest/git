#include "texmanager.hpp"

void TextureManager::Init(SDL_Renderer* renderer)
{
    r = renderer;
}

int total_tex_delta=0;
SDL_Texture* TextureManager::GetTexture(const std::string& path) {
    if (path == "") return 0x0;
    SDL_Log("---\n[TEXM] PreGetTexture: Total texture delta is %d\n", total_tex_delta);
    for (TexEntry& tex : tex_list) {
        SDL_Log("[TEXM] PreGetTexture: Texture %s has %d uses\n", tex.path.c_str(), tex.refcount);
    };
    SDL_Log("---\n");
    for (TexEntry& tex : tex_list) {
        if (tex.path == path) {
            tex.refcount += 1;
            total_tex_delta += 1;
            SDL_Log("[TEXM] Texture %s gains a use, now at %d\n",tex.path.c_str(), tex.refcount);
            SDL_Log("---\n[TEXM] PostGetTexture: Total texture delta is %d\n", total_tex_delta);
            for (TexEntry tex : tex_list) {
                SDL_Log("[TEXM] PostGetTexture: Texture %s has %d uses\n", tex.path.c_str(), tex.refcount);
            };
            SDL_Log("---\n");
            return tex.texture;
        };
    };
    SDL_IOStream* io = SDL_IOFromFile(path.c_str(), "rb");
//    SDL_Surface* s = SDL_LoadPNG(path.c_str());
    SDL_Surface* s = SDL_LoadPNG_IO(io, true);
    if (!s) { SDL_Log("Failed to load png!\n");  return nullptr; };
    SDL_Texture* t = SDL_CreateTextureFromSurface(r, s);
    SDL_Log("During image load: %s\n", SDL_GetError());
    TexEntry e;
    e.path = path;
    e.refcount = 1;
    total_tex_delta += 1;
    e.texture = t;
    SDL_DestroySurface(s);
    tex_list.emplace_back(e);
    SDL_Log("---\n[TEXM] PostGetTexture: Total texture delta is %d\n", total_tex_delta);
    for (TexEntry& tex : tex_list) {
        SDL_Log("[TEXM] PostGetTexture: Texture %s has %d uses\n", tex.path.c_str(), tex.refcount);
    };
    SDL_Log("---\n");
    return e.texture;
};

void TextureManager::FreeTexture(const std::string& path) {
    if (path == "") return;
    SDL_Log("---\n[TEXM] PreFreeTexture: Total texture delta is %d\n", total_tex_delta);
    for (TexEntry& tex : tex_list) {
        SDL_Log("[TEXM] PreFreeTexture: Texture %s has %d uses\n", tex.path.c_str(), tex.refcount);
    };
    SDL_Log("---\n");
    SDL_Log("[TEXM] FreeTexture entered with path %s\n", path.c_str());
    for (TexEntry& tex : tex_list) {
        if (tex.path == path) {
            tex.refcount -= 1;
            total_tex_delta -= 1;
            SDL_Log("[TEXM] FreeTexture: Texture %s has %d uses now\n",tex.path.c_str(), tex.refcount);
        };
    };
    SDL_Log("---\n[TEXM] PostFreeTexture: Total texture delta is %d\n", total_tex_delta);
    for (TexEntry& tex : tex_list) {
        SDL_Log("[TEXM] PostFreeTexture: Texture %s has %d uses\n", tex.path.c_str(), tex.refcount);
    };
    SDL_Log("---\n");
};

void TextureManager::TrimTextures() {
    SDL_Log("---\n[TEXM] Total texture delta is %d\n", total_tex_delta);
    for (TexEntry& tex : tex_list) {
        SDL_Log("[TEXM] TrumTextures: Texture %s has %d uses\n",tex.path.c_str(),tex.refcount);
        if (tex.refcount <= 0 && tex.texture){
            SDL_Log("[TEXM] We are erasing texture %s\n",tex.path.c_str());
            SDL_DestroyTexture(tex.texture);
            tex.texture = nullptr;
            tex.path = "";
        };
    };
    SDL_Log("---\n[TEXM] TrimTextures end\n");
};

TextureManager g_TexManager;