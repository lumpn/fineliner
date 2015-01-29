#ifndef SNAKE_HPP_
#define SNAKE_HPP_

#include "int2.hpp"
#include "dir2.hpp"

class Game;

class Snake {

    public:
        explicit Snake(int2 position, dir2 direction);
        ~Snake();

        int2 GetPosition() const;
        dir2 GetDirection() const;
        int GetEnergy() const;

        void SetPosition(int2 position);
        void SetDirection(dir2 direction);
        void SetStepSize(int stepSize, int duration);
        void IncEnergy(int delta);
        void DecEnergy(int delta);
        void Update(Game* game);
        void Die();
        void Jump();

        int GetNumDeaths() const;

    private:
        int2 position;
        dir2 direction;
        int stepSize;
        int duration;
        int energy;
        bool jump;

        int numDeaths;

    private:
        static const int initialEnergy = 50;
        static const int maxEnergy = 100;
        static const int jumpSize = 10;
};

#endif /* SNAKE_HPP_ */
