#include <math.h>
#pragma once
class Vector2D
{
private:
	int x;
	int y;

public:
	Vector2D() : x(0), y(0) {};
	Vector2D(int x, int y) : x(x), y(y) {};

#pragma region GETTERS
	int getY() const { return y; };
	int getX() const { return x; };

	void setX(int _x) { x = _x; };
	void setY(int _y) {y = _y; };
#pragma endregion

#pragma region OPERATORS

	Vector2D operator+(const Vector2D& v) const;
	Vector2D operator-(const Vector2D& v) const;
	Vector2D operator*(int n) const;

	int module();
	void normalize();
	int operator*(const Vector2D& v) const;
	bool operator==(const Vector2D& v) const;
	bool operator!=(const Vector2D& v)const;
	Vector2D oposite() const { return Vector2D(-x, -y); }
#pragma endregion
};

using Point2D = Vector2D;

