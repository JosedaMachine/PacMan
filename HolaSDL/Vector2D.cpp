#include "Vector2D.h"
#include "checkML.h"

//Operadores

//Operador de suma
Vector2D Vector2D::operator+(const Vector2D& v) const
{
	return Vector2D(x + v.x, y + v.y);
}
//Operador de resta
Vector2D Vector2D::operator-(const Vector2D& v) const
{
	return Vector2D(x-v.x , y-v.y);
}
//Operador de multiplicación por un número
Vector2D Vector2D::operator*(int n) const
{
	return Vector2D(x * n, y * n);
}
//calcula el modulo de un vector
int Vector2D::module()
{
	return sqrt(x*x + y*y);
}
//normaliza un vector
void Vector2D::normalize()
{
	if (x != 0)
	{
		x /= abs(x);
	}

	if (y != 0)
	{
		y /= abs(y);
	}

}
//Operador de vector por vector
int Vector2D::operator*(const Vector2D& v) const
{
	return x*v.x + y*v.y;
}
//Operador de igualdad
bool Vector2D::operator==(const Vector2D& v) const
{
	return (x == v.x && y == v.y);
}
//Operador de diferencia
bool Vector2D::operator!=(const Vector2D& v) const
{
	return v.y != y || v.x != x;
}

