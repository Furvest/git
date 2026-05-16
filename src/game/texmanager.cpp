#include "texmanager.hpp"

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
    SDL_IOStream* io = SDL_IOFromFile(path.c_str(), "rb");
//    SDL_Surface* s = SDL_LoadPNG(path.c_str());
    SDL_Surface* s = SDL_LoadPNG_IO(io, true);
    if (!s) { printf("failed to load png!\n");  return nullptr; };
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

TextureManager g_TexManager;