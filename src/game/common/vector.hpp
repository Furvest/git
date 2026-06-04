/**
 * @file vector.hpp
 * @brief Заголовочный файл для вектора
 *
 * Структуры, опсианные в этом файле используются для определения положения мыши,
 * а также для отрисовки текстур, которые должны находиться в определенной позициии
 *
 */

#pragma once

/**
  * @class Vector
  * @brief Структура вектора
  * 
  * Поля: координаты по x и y
  * Методы: перегрузки операторов + и -
  * 
  */

struct Vector {
	Vector(float X, float Y) :x(X), y(Y) {};
	Vector() {};
	Vector operator+(const Vector& other) const { return Vector(x + other.x, y + other.y); };
	Vector operator-(const Vector& other) const { return Vector(x - other.x, y - other.y); };
	float x=0.0;
	float y=0.0;
};

/**
* @class Quad
* @brief Структура прямоугольника
*
* Составляется из двух векторов
*
*/

struct Quad {
	Quad(float X, float Y, float XX, float YY){
		topleft.x = X;
		topleft.y = Y;
		widthheight.x = XX;
		widthheight.y = YY;
	};
	Vector topleft;
	Vector widthheight;
};
