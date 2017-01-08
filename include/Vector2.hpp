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
    Vector2<T> operator*(T scalar);
    Vector2<T> operator/(T scalar);
    void operator+=(const Vector2<T>& other);
    void operator-=(const Vector2<T>& other);
    bool operator==(const Vector2<T>& other);

    T lengthSqr();
    T length();
    Vector2<T> normalise();
};

typedef Vector2<float> Vector2f;
typedef Vector2<int> Vector2i;
typedef Vector2<unsigned int> Vector2u;