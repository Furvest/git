#pragma once
#include <string>
#include <vector>
#include <SDL3/SDL.h>
struct TexEntry {
	std::string path;
	SDL_Texture* texture = nullptr;
	int refcount = 0;
};

class TextureManager {
	SDL_Renderer* r=nullptr;
	std::vector<TexEntry> tex_list;
public:
	void Init(SDL_Renderer* renderer);
	//TODO: обдумать передумать
	SDL_Texture* GetTexture(const std::string& path);
	void FreeTexture(const std::string& path);
	void TrimTextures();

};
extern TextureManager g_TexManager;