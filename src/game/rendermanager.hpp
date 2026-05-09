#pragma once
#include <SDL3/SDL.h>
#include "common/vector.hpp"
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

struct ColorDesc {
	double R=1.0;
	double G=1.0;
	double B=1.0;
	double A=1.0;
};

class Renderer {
	SDL_Renderer* r=nullptr;
public:
	Vector GetScreenSize();
	float globalScale = 1.0f;
	TTF_Font* main_font = 0x0;
	TTF_TextEngine* text_engine = 0x0;
	Renderer();
	void Init(SDL_Renderer* renderer);
	void Render(SDL_Texture* tex, Vector pos, Quad crop_region, Vector pivot, Vector scale, double rotation,ColorDesc color);
	void RenderFont(const std::string& text, Vector pos);
};

extern Renderer g_Renderer;