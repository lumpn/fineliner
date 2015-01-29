#include "int2.hpp"

int2::int2()
        : x(0), y(0) {
}

int2::int2(int x_, int y_)
        : x(x_), y(y_) {
}

int2::int2(const int2& other)
        : x(other.x), y(other.y) {
}

int2::~int2() {
}

void int2::operator=(const int2& other) {
    x = other.x;
    y = other.y;
}

void int2::operator+=(const int2& other) {
    x += other.x;
    y += other.y;
}

void int2::operator*=(int scale) {
    x *= scale;
    y *= scale;
}

int2 int2::operator*(int scale) const {
    int2 result = *this;
    result *= scale;
    return result;
}

int int2::distanceSqr(const int2& a, const int2& b) {
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    return (dx * dx + dy * dy);
}
