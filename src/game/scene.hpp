/**
 * @file scene.hpp
 * @brief Заголовочный файл для сцен
 * 
 * Сцены в контексте данной игры имеют большое значение - они являются составной частью всего визуала
 *
 */

#pragma once
#include "rendermanager.hpp"
#include "common/vector.hpp"
#include <SDL3/SDL.h>

/**
 * @class Scene
 * @brief Класс сцены
 *
 * Приватное поле: состояние сцены
 * Публичные поля: номер в очереди, статус нахождения в очереди на удаление
 * Методы: обновление, отрисовка, проверки на состояние сцены, обработка ивентов
 */

class Scene {
	bool isFocused = true;
public:
	int sortPriority = 0;
	bool queueForRemoval = false;
	virtual ~Scene() { SDL_Log("scene destructor"); };
	virtual bool Update(float delta) { return true; };
	virtual bool Render(float delta) { return true; };
	virtual bool IsFocused() { return isFocused; };
	virtual bool Focus() { isFocused = true; return true; };
	virtual bool Unfocus() { isFocused = false; return true; };
	virtual bool HandleEvent(SDL_Event* e) { return true; };
};
