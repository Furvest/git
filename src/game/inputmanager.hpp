/**
 * @file inputmanager.hpp
 * @brief Заголовочный файл обработчика ввода
 *
 * Используется для обработки пользовательского ввода
 *
 */

#pragma once
#include "common/vector.hpp"

/**
* @class InputManager
* @brief Класс обработчика пользовательского ввода
*
* Поля: координаты курсора на экране, состояния левой кнопки мыши
* Методы: получение позиции курсора в формате вектора Vector, 
* Инициализация, осуществление ивента и проверка на зажатую ЛКМ
* 
*/

class InputManager {
	
	int mouse_x, mouse_y;
	bool lmb_press;
	bool lmb_trigger;
public:
	Vector GetMousePosition();
	bool IsLeftClickPressed();
	void Init();
	void ProcessEvent();
};
