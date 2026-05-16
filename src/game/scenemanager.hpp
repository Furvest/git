#pragma once
#include "scene.hpp"
#include <list>
#include <memory>
class SceneManager {
	std::list<std::unique_ptr<Scene>> ScenesToAdd;
	bool orderChanged = false;
public:
	std::list<std::unique_ptr<Scene>> SceneList;
	void QueueScene(std::unique_ptr<Scene> s);
	bool UpdateQueue();
	bool Update(float delta);
	bool Render(float delta);
	bool HandleEvent(SDL_Event* e);
};