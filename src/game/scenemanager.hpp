#pragma once
#include "scene.hpp"
#include <list>
#include <memory>
class SceneManager {
public:
	std::list<std::unique_ptr<Scene>> SceneList;
	bool Update(float delta);
	bool Render(float delta);
	bool HandleEvent(SDL_Event* e);
};