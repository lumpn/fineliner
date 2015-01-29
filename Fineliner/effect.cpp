#include "effect.hpp"

Effect::Effect(int duration_)
        : duration(duration_) {
}

Effect::~Effect() {
}

void Effect::Update() {
    duration--;
}

bool Effect::IsActive() const {
    return duration > 0;
}
