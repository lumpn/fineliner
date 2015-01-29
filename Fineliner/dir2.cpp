#include "dir2.hpp"

dir2::dir2()
        : value(DIR_UP) {
}

dir2::dir2(dir value_)
        : value(value_) {
}

dir2::dir2(const dir2& other)
        : value(other.value) {
}

dir2::~dir2() {
}

bool dir2::operator==(const dir2& other) const {
    return value == other.value;
}

void dir2::operator=(const dir2& other) {
    value = other.value;
}

int2 dir2::ToInt2() const {
    switch (value) {
        case DIR_UP:
            return int2(0, 1);
        case DIR_DOWN:
            return int2(0, -1);
        case DIR_LEFT:
            return int2(-1, 0);
        case DIR_RIGHT:
            return int2(1, 0);
        default:
            return int2(0, 0);
    }
}

dir2 dir2::Opposite() const {
    switch (value) {
        case DIR_UP:
            return dir2(DIR_DOWN);
        case DIR_DOWN:
            return dir2(DIR_UP);
        case DIR_LEFT:
            return dir2(DIR_RIGHT);
        case DIR_RIGHT:
            return dir2(DIR_LEFT);
        default:
            return dir2(DIR_NONE);
    }
}

dir2 dir2::None() {
    return dir2(DIR_NONE);
}

dir2 dir2::Up() {
    return dir2(DIR_UP);
}

dir2 dir2::Down() {
    return dir2(DIR_DOWN);
}

dir2 dir2::Left() {
    return dir2(DIR_LEFT);
}

dir2 dir2::Right() {
    return dir2(DIR_RIGHT);
}
