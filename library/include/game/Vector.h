#pragma once

template <typename T>
struct Vector2 {
    T x, y;
    Vector2<T> operator+(Vector2<T> other) {
        return Vector2<T>(this.x + other.x, this.y + other.y)
        }
    Vector2<T> operator-(Vector2<T> other)
    {
    return Vector2<T>(this.x + other.x, this.y + other.y)
    }
    Vector2<T> operator/(Vector2<T> other)
    {
    return Vector2<T>(this.x + other.x, this.y + other.y)
    }
    Vector2<T> operator%(Vector2<T> other)
    {
    return Vector2<T>(this.x + other.x, this.y + other.y)
    }
};
typedef Vector2<unsigned> uvec2;
typedef Vector2<int> vec2;


