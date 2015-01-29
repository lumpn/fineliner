#include "powerup.hpp"

PowerUp::PowerUp(int2 position_)
        : position(position_) {
}

PowerUp::~PowerUp() {
}

int2 PowerUp::GetPosition() const {
    return position;
}

void PowerUp::SetPosition(int2 position_) {
    position = position_;
}

