#pragma once
struct Vector {
	Vector(double X, double Y) :x(X), y(Y) {};
	Vector() {};
	Vector operator+(const Vector& other) const { return Vector(x + other.x, y + other.y); };
	Vector operator-(const Vector& other) const { return Vector(x - other.x, y - other.y); };
	double x=0.0;
	double y=0.0;
};

struct Quad {
	Quad(double X, double Y, double XX, double YY){
		topleft.x = X;
		topleft.y = Y;
		widthheight.x = XX;
		widthheight.y = YY;
	};
	Vector topleft;
	Vector widthheight;
};