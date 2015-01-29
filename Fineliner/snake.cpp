#include "snake.hpp"
#include "game.hpp"

Snake::Snake(int2 position_, dir2 direction_)
        : position(position_), direction(direction_), stepSize(1), energy(initialEnergy), numDeaths(0) {
}
Snake::~Snake() {
}

int2 Snake::GetPosition() const {
    return position;
}

dir2 Snake::GetDirection() const {
    return direction;
}

int Snake::GetEnergy() const {
    return energy;
}

void Snake::SetPosition(int2 position_) {
    position = position_;
}

void Snake::SetDirection(dir2 direction_) {
    direction = direction_;
}

void Snake::SetStepSize(int stepSize_) {
    stepSize = stepSize_;
}

void Snake::IncEnergy(int delta) {
    energy += delta;
}

void Snake::DecEnergy(int delta) {
    energy -= delta;
}

void Snake::Update(Game* game) {

    // update energy
    if (energy < maxEnergy)
        energy++;

    // update position
    if (direction.value == dir2::DIR_NONE)
        return;

    position += direction.ToInt2() * stepSize;

    // collision?
    if (!game->IsCellFree(position)) {
        Die();
        game->Restart();
    }
}

void Snake::Die() {
    direction = dir2::None();
    numDeaths++;
}

int Snake::GetNumDeaths() const {
    return numDeaths;
}
