#ifndef TELEPORT_POWERUP_HPP_
#define TELEPORT_POWERUP_HPP_

#include "powerup.hpp"

class Snake;
class Game;
class Texture;

class TeleportPowerUp: public PowerUp {

    public:
        explicit TeleportPowerUp(int2 position);
        virtual ~TeleportPowerUp();

        virtual void Render(Texture* target, const Game& game) const;
        virtual void OnTrigger(Snake* snake, Snake* other, Game* game);

    private:
        static const int eraserRadius = 30;
};

#endif /* TELEPORT_POWERUP_HPP_ */
