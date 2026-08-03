
#pragma once

#include <cmath>

struct Vec2 {
    double x = 0.0;
    double y = 0.0;

    [[nodiscard]] double lengthSquared() const {
        return x * x + y * y;
    }

    [[nodiscard]] double length() const {
        return std::sqrt(lengthSquared());
    }

    [[nodiscard]] double dot(const Vec2& other) const {
        return x * other.x + y * other.y;
    }

    Vec2& operator+=(const Vec2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vec2& operator-=(const Vec2& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vec2& operator*=(double scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Vec2& operator/=(double scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }
};

inline Vec2 operator+(Vec2 left, const Vec2& right) {
    return left += right;
}

inline Vec2 operator-(Vec2 left, const Vec2& right) {
    return left -= right;
}

inline Vec2 operator*(Vec2 vector, double scalar) {
    return vector *= scalar;
}

inline Vec2 operator*(double scalar, Vec2 vector) {
    return vector *= scalar;
}

inline Vec2 operator/(Vec2 vector, double scalar) {
    return vector /= scalar;
}