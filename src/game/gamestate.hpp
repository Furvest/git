/**
 * @file gamestate.hpp
 * @brief Заголовочный файл состояния игры
 *
 */

#pragma once
#include <string>

/**
   * @class GameState
   * @brief Структура состояния игры
   *
   * Единственное поле - текущая локация
   * 
   */

struct GameState {
	std::string cur_field="test_field";
};

extern GameState g_GameState;
