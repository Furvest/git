#pragma once
#include "game.hpp"
#include "texmanager.hpp"

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
	std::string game_dir;
	SDL_Window* w = 0x0;
	SDL_Renderer* r = 0x0;
	Game g;		//пока что всё очень кривое сырое, потом обдумаю как всё сделать хорошо, извините!!!
	bool DidQuit = false;
};
extern Manager g_Manager;