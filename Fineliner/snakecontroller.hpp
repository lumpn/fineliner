#ifndef SNAKECONTROLLER_HPP_
#define SNAKECONTROLLER_HPP_

#include "dir2.hpp"

class Snake;

class SnakeController {
    public:
        explicit SnakeController(Snake* snake);
        ~SnakeController();

        void Update();

        bool Steer(dir2 direction);
        bool Jump();

    private:
        Snake* snake;

    private:
        static const int steerEnergy = 10;
        static const int jumpEnergy = 60;

        static const int defaultStepSize = 1;
        static const int jumpStepSize = 10;
};

#endif /* SNAKECONTROLLER_HPP_ */
