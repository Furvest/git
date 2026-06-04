/**
 * @file titlescene.hpp
 * @brief Заголовочный файл начального экрана
 *
 * Здесь объявлен класс TitleScene, который наследуется от базового Scene.
 * Это начальный экран игры
 * 
 */

#pragma once
#include "scene.hpp"
#include "anm2sprite.hpp"
#include "manager.hpp"

/**
 * @class TitleScene
 * @brief Класс начального экрана
 *
 * Поля: спрайты anm2 с заголовком, кнопкой "начать" и "выйти"
 * Методы: обновление, отрисовка, обработка событий, закрытие сцены
 * 
 */

class TitleScene : public Scene {
	ANM2::Sprite title;
	ANM2::Sprite begin_button;
	ANM2::Sprite quit_button;
public:
	TitleScene();
	~TitleScene();
	bool Update(float delta) override;
	bool Render(float delta) override;
	bool HandleEvent(SDL_Event* e) override;
	bool Focus() override { Scene::Focus(); return false; };
	bool Unfocus() override { Scene::Unfocus(); return false; }
}; 
