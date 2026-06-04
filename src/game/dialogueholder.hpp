/**
 * @file dialogueholder.hpp
 * @brief Заголовочный файл обработчика диалогов
 *
 * Здесь содержится объявление класса TextureManager, отвечающего за обработку диалогов 
 * главного героя с другими персонажами
 * 
 */

#pragma once
#include <string>

 /**
   * @class DialogueHolder
   * @brief Обработчик диалогов
   *
   * Имеет 3 приватных поля: заголовок, текст и состояние (показан ли)
   *
   */

struct DialogueHolder {
	std::string header;
	std::string text;
	bool isShown;
};
