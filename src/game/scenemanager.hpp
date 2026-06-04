/**
 * @file scanemanager.hpp
 * @brief Заголовочный файл менеджера сцен
 *
 * Здесь объявлен класс SceneManager, который управляет сценами
 *
 */

#pragma once
#include "scene.hpp"
#include <list>
#include <memory>

/**
 * @class SceneManager
 * @brief класс менеджера сцен
 *
 * Поля: список уникальных указателей на объекты класса Scene (сцены на добавление), список сцен и 
 * флаг, указывающий, не изменен ли порядок сцен
 * 
 * Методы: создание очереди сцен, обновление очереди, обновление, отрисовка и обработка событий
 */

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
