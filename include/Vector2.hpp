#pragma once

template <typename T>
class Vector2
{
public:
	T x, y;

	Vector2();
	Vector2(T x, T y);
	Vector2<T> operator+(const Vector2<T>& other) const;
	Vector2<T> operator-(const Vector2<T>& other) const;
	Vector2<T> operator*(float scalar);
	void operator+=(const Vector2<T>& other);
	void operator-=(const Vector2<T>& other);

	static Vector2<T> lerp(const Vector2<T>& start, const Vector2<T>& end, float percent);
};

template <typename T>
Vector2<T> operator*(float left, Vector2<T> right);

typedef Vector2<float> Vector2f;
typedef Vector2<int> Vector2i;
typedef Vector2<unsigned int> Vector2u;