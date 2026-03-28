#pragma once

#include "anm2.hpp"
#include <SDL3/SDL.h>
#include <vector>

//class EngineTexture {
//	std::string _path;
//	SDL_Texture* tex=nullptr;
//	int refcount = 0;
//public:
//	EngineTexture(const std::string& path);
//	void DecRef();
//	void IncRef();
//	~EngineTexture();
//	friend class TextureManager;
//};
//class EngineTextureRef {
//	int _tex_idx = -1;
//public:
//	EngineTextureRef(std::vector<EngineTexture>* tex_list,int tex_idx);
//	~EngineTextureRef();
//};
//class TextureManager {
//	std::vector<EngineTexture> tex_list;
//	EngineTextureRef GetTex(const std::string& path);
//};

struct TexEntry {
    std::string  path;
    SDL_Texture* texture  = nullptr;
    int          refcount = 0;
};

class TextureManager {
    SDL_Renderer*         r;
    std::vector<TexEntry> tex_list;

  public:
    void Init(SDL_Renderer* renderer);
    //TODO: обдумать передумать
    SDL_Texture* GetTexture(const std::string& path);
    void         FreeTexture(const std::string& path);
    void         TrimTextures();
};

extern TextureManager g_TexManager;

struct GameTexEntry {
    std::string  path;
    SDL_Texture* texture = nullptr;
};

class Game {
    GameTexEntry test_tex;
    double       counter = 0;

  public:
    void Init();
    void Render();
    void Deinit();
};

class Manager {
  public:
    void Init();
    void Update();
    void Render();
    void Shutdown();
    bool IsShutdown() {
        return DidQuit;
    };
    //пока что без private, сначала надо чтобы хоть что-то работало ;p
    std::string       game_dir;
    SDL_Window*       w = 0x0;
    SDL_Renderer*     r = 0x0;
    std::vector<ANM2> v; //temp
    Game              g; //пока что всё очень кривое сырое, потом обдумаю как всё сделать хорошо, извините!!!
    bool              DidQuit = false;
};
extern Manager g_Manager;
