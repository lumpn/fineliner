#include "snakecontroller.hpp"
#include "snake.hpp"

SnakeController::SnakeController(Snake* snake_)
        : snake(snake_) {
}

SnakeController::~SnakeController() {
}

void SnakeController::Update() {
    snake->SetStepSize(defaultStepSize);
}

bool SnakeController::Steer(dir2 direction) {
    if (direction == snake->GetDirection()) {
        return false;
    }
    if (direction == snake->GetDirection().Opposite()) {
        return false;
    }
    if (snake->GetEnergy() < steerEnergy) {
        return false;
    }
    snake->SetDirection(direction);
    snake->DecEnergy(steerEnergy);
    return true;
}

bool SnakeController::Jump() {
    if (snake->GetEnergy() < jumpEnergy) {
        return false;
    }
    snake->SetStepSize(jumpStepSize);
    snake->DecEnergy(jumpEnergy);
    return true;
}
