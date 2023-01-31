#pragma once

template <typename T>
struct Vector2 {
    T x, y;

    Vector2(T x, T y)
    : x(x), y(y) {}

    Vector2()
    : Vector2(0,0) {}

    // ADDITION / SUB

    Vector2<T> operator+(Vector2<T> other) {
        return Vector2<T>(this->x + other.x, this->y + other.y);
    }

    Vector2<T> operator-(Vector2<T> other) {
        return Vector2<T>(this->x - other.x, this->y - other.y);
    }

    // BOOLEANS

    bool operator==(Vector2<T> other) {
        return (this->x == other.x && this->y == other.y);
    }

    bool operator>(Vector2<T> other) {
        return (this->x > other.x || this->y > other.y);
    }

    bool operator>=(Vector2<T> other) {
        return (this->x >= other.x || this->y >= other.y);
    }

    bool operator<(Vector2<T> other) {
        return (this->x < other.x || this->y < other.y);
    }

    bool operator<=(Vector2<T> other) {
        return (this->x <= other.x || this->y <= other.y);
    }

    // OTHER UTILS

    template <typename T2>
    Vector2<T> operator/(T2 other) {
        return Vector2<T>(this->x / other, this->y / other);
    }

    template <typename T2>
    Vector2<T> operator%(T2 other) {
        return Vector2<T>(this->x % other, this->y % other);
    }
    
};

typedef Vector2<unsigned> uvec2;
typedef Vector2<int> vec2;


