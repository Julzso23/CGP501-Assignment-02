#include "Vector2.hpp"
#include <cmath>

template<typename T>
Vector2<T>::Vector2() :
	x((T)0),
	y((T)0)
{
}

template <typename T>
Vector2<T>::Vector2(T x, T y) :
	x(x),
	y(y)
{
}

template<typename T>
Vector2<T> Vector2<T>::operator+(const Vector2<T>& other) const
{
	return Vector2<T>(x + other.x, y + other.y);
}

template<typename T>
Vector2<T> Vector2<T>::operator-(const Vector2<T>& other) const
{
	return Vector2<T>(x - other.x, y - other.y);
}

template<typename T>
Vector2<T> Vector2<T>::operator*(T scalar)
{
	return Vector2<T>(x * scalar, y * scalar);
}

template<typename T>
Vector2<T> Vector2<T>::operator/(T scalar)
{
	return operator*((T)1 / scalar);
}

template<typename T>
void Vector2<T>::operator+=(const Vector2<T>& other)
{
	x += other.x;
	y += other.y;
}

template<typename T>
void Vector2<T>::operator-=(const Vector2<T>& other)
{
	x -= other.x;
	y -= other.y;
}

template<typename T>
bool Vector2<T>::operator==(const Vector2<T>& other)
{
    return (x == other.x) && (y == other.y);
}

template<typename T>
T Vector2<T>::lengthSqr()
{
	return (T)(pow(x, 2) + pow(y, 2));
}

template<typename T>
T Vector2<T>::length()
{
	return (T)sqrt(lengthSqr());
}

template<typename T>
Vector2<T> Vector2<T>::normalise()
{
	return operator/(length());
}

template Vector2<float>;
template Vector2<int>;
template Vector2<unsigned int>;
