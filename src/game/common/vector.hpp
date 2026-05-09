#pragma once
struct Vector {
	Vector(float X, float Y) :x(X), y(Y) {};
	Vector() {};
	Vector operator+(const Vector& other) const { return Vector(x + other.x, y + other.y); };
	Vector operator-(const Vector& other) const { return Vector(x - other.x, y - other.y); };
	float x=0.0;
	float y=0.0;
};

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