/**
 * @file manager.hpp
 * @brief Заголовочный файл для менеджера
 *
 * Используется для управления всеми сценами
 *
 */

#pragma once
#include "texmanager.hpp"
#include "scenemanager.hpp"

/**
  * @class Manager
  * @brief Класс общего менеджера
  *
  * Методы: инициализация, обновление, отрисвока, закрытие.
  * Используется для обобщенного управления сценами
  * 
  */

class Manager {
	uint64_t prev_ticks = 0;
	float delta = 0.0;
public:
	void Init();
	void Update();
	void Render();
	void Shutdown();
	bool IsShutdown() {
		return DidQuit;
	};
	SceneManager sceneManager;
	//пока что без private, сначала надо чтобы хоть что-то работало ;p
	std::string game_dir;
	SDL_Window* w = 0x0;
	SDL_Renderer* r = 0x0;
	bool DidQuit = false;
};
extern Manager g_Manager;
