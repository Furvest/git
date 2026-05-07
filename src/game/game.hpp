#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include "anm2data.hpp"
#include "anm2sprite.hpp"


struct GameTexEntry {
	std::string path;
	SDL_Texture* texture = nullptr;
};


class Game {
	ANM2::Sprite test_spr;
	GameTexEntry test_tex;
	int counter = 0;
public:
	void Init();
	void Render();
	void Deinit();
};

