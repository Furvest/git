#pragma once
#include "rendermanager.hpp"
#include "common/vector.hpp"
#include <SDL3/SDL.h>

class Scene {
	bool isFocused = true;
public:
	virtual ~Scene() = default;
	virtual bool Update(float delta) = 0;
	virtual bool Render(float delta) = 0;
	virtual bool Focus() = 0;
	virtual bool Unfocus() = 0;
	virtual bool HandleEvent(SDL_Event* e) = 0;
};