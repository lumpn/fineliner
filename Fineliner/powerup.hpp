#ifndef POWERUP_HPP_
#define POWERUP_HPP_

#include "int2.hpp"

class Snake;
class Game;
class Texture;

class PowerUp {
    public:
        explicit PowerUp(int2 position);
        virtual ~PowerUp() = 0;

        void SetPosition(int2 position);
        int2 GetPosition() const;

        virtual void Render(Texture* target, const Game& game) const = 0;

        virtual void OnTrigger(Snake* snake, Snake* other, Game* game) = 0;

    private:
        int2 position;
};

#endif /* POWERUP_HPP_ */
