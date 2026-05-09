#pragma once
#include <SDL3/SDL.h>
#include "common/vector.hpp"

struct ColorDesc {
	double R=1.0;
	double G=1.0;
	double B=1.0;
	double A=1.0;
};

class Renderer {
	SDL_Renderer* r=nullptr;
public:
	float globalScale = 2.0f;
	Renderer();
	void Init(SDL_Renderer* renderer);
	void Render(SDL_Texture* tex, Vector pos, Quad crop_region, Vector pivot, Vector scale, double rotation,ColorDesc color);
};

extern Renderer g_Renderer;