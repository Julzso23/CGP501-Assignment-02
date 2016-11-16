#include "Vector2.hpp"

template<typename T>
Vector2<T>::Vector2() :
	x(0.f),
	y(0.f)
{
}

template <typename T>
Vector2<T>::Vector2(T x, T y) :
	x(x),
	y(y)
{
}

template<typename T>
Vector2<T> Vector2<T>::operator+(const Vector2<T>& other)
{
	return Vector2<T>(x + other.x, y + other.y);
}

template<typename T>
Vector2<T> Vector2<T>::operator-(const Vector2<T>& other)
{
	return Vector2<T>(x - other.x, y - other.y);
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

template Vector2<float>;
template Vector2<int>;
template Vector2<unsigned int>;
