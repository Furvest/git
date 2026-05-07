#pragma once
#include <string>
#include <SDL3/SDL.h>
class FSManager {
public:
	static std::string GetAssetPath() { return std::string(SDL_GetBasePath())+"assets/"; };
};