#pragma once
#include <string>
#include <SDL3/SDL.h>
#include <filesystem>
class FSManager {
public:
	static std::filesystem::path GetAssetFSPath() { return (std::filesystem::path(SDL_GetBasePath()) / "assets"); };
	static std::string GetAssetPath() { return std::string(SDL_GetBasePath())+"assets/"; };
};