/**
 * @file rendermanager.hpp
 * @brief Заголовочный файл менеджера отрисовщика
 *
 * Здесь содержится объявление класса Renderer, отвечающего за отрисовку текстур и текста
 * Класс работает на основе встроенного отрисовщика SDL_Renderer 
 */

#pragma once
#include <SDL3/SDL.h>
#include "common/vector.hpp"
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

/**
 * @class ColorDesc
 * @brief Структура цвета
 *
 * Имеет 4 поля: R, G, B и A
 * Определяет цвет в модели RGB, A - альфа-канал
 * 
 */

struct ColorDesc {
	double R=1.0;
	double G=1.0;
	double B=1.0;
	double A=1.0;
};

/**
 * @class Renderer
 * @brief Отрисовщик текстур
 *
 * Приватное поле - ссылка на объект SDL_Renderer
 * Публичные поля: глобальный масштаб, шрифт, движок текста
 * Методы: инициализация, отрисовка текстур, шрифта и центрированного шрифта
 */

class Renderer {
	SDL_Renderer* r=nullptr;
public:
	Vector GetScreenSize();
	float globalScale = 1.0f;
	TTF_Font* main_font = 0x0;
	TTF_TextEngine* text_engine = 0x0;
	Renderer();
	void Init(SDL_Renderer* renderer);
	void Render(SDL_Texture* tex, Vector pos, Quad crop_region, Vector pivot, Vector scale, double rotation,ColorDesc color);
	void RenderFont(const std::string& text, Vector pos);
	void RenderFontCentered(const std::string& text, Vector pos);
};

extern Renderer g_Renderer;
