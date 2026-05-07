#pragma once
#include <SDL3/SDL.h>
#include "common/vector.hpp"
class Renderer {
	SDL_Renderer* r=nullptr;
public:
	Renderer();
	void Init(SDL_Renderer* renderer);
	void Render(SDL_Texture* tex, Vector pos, Quad crop_region, Vector pivot, Vector scale, double rotation);
};

extern Renderer g_Renderer;