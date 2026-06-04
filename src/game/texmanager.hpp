/**
 * @file texmanager.hpp
 * @brief Заголовочный файл менеджера текстур
 *
 * Здесь содержится объявление класса TextureManager, отвечающего за операции с текстурами
 * Помимо этого, присутствует объявление структуры TexEntry, объекты которой образуют список текстур
 */

#pragma once
#include <string>
#include <vector>
#include <SDL3/SDL.h>

/**
 * @class TexEntry
 * @brief Структура вхождения тестуры
 *
 * Поля: путь к текстуре, ссылка на объект класса SDL_Texture и количество ссылок на текстуру
 */

struct TexEntry {
	std::string path;
	SDL_Texture* texture = nullptr;
	int refcount = 0;
};

/**
 * @class TextureManager
 * @brief Менеджер текстур - управляет текстурами
 *
 * Поля: ссылка на SDL_Renderer, вектор текстур типа TexEntry
 * Методы: инициализация, получение, очистка и вывод текстуры
 */

class TextureManager {
	SDL_Renderer* r=nullptr;
	std::vector<TexEntry> tex_list;
public:
	void Init(SDL_Renderer* renderer);
	//TODO: обдумать передумать
	SDL_Texture* GetTexture(const std::string& path);
	void FreeTexture(const std::string& path);
	void TrimTextures();

};
extern TextureManager g_TexManager;
