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
	float fractional_counter=0.0f;
	uint64_t prev_ticks = 0;
public:
	void Init();
	void Update();
	void Render();
	void ProcessClick(Vector click_pos);
	void Deinit();
};

