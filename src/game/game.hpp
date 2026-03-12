#pragma once
#include <SDL3/SDL.h>
#include "anm2.hpp"
class Manager {
public:
	void Init();
	void Update();
	void Shutdown();
	bool IsShutdown() {
		return DidQuit;
	};
private:
	std::string game_dir;
	SDL_Window* w = 0x0;
	SDL_Event event_holder;
	std::vector<ANM2> v;	//temp
	bool DidQuit = false;
};