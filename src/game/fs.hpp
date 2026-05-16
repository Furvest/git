#pragma once
#include <string>
#include <SDL3/SDL.h>
#include <filesystem>
class FSManager {
public:
#ifndef ANDROID
	static std::filesystem::path GetAssetFSPath() { return (std::filesystem::path(SDL_GetBasePath()) / "assets"); };
	static std::string GetAssetPath() { return std::string(SDL_GetBasePath())+"assets/"; };
#endif
#ifdef ANDROID
	static std::filesystem::path GetAssetFSPath() { return std::filesystem::path(""); };
	static std::string GetAssetPath() { return ""; };
#endif
};