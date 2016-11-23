#include "Vector2.hpp"

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
Vector2<T> Vector2<T>::operator*(float scalar)
{
	return Vector2<T>(x * scalar, y * scalar);
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
Vector2<T> Vector2<T>::lerp(const Vector2<T>& start, const Vector2<T>& end, float percent)
{
	return start + percent * (end - start);
}

template <typename T>
Vector2<T> operator*(float left, Vector2<T> right)
{
	return right * left;
}

template Vector2<float>;
template Vector2<int>;
template Vector2<unsigned int>;
